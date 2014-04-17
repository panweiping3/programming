commit aab4874355679c70f93993cf3b3fd74643b9ac33
Author: Yuchung Cheng <ycheng@google.com>
Date:   Thu Jul 19 06:43:10 2012 +0000

    net-tcp: Fast Open client - detecting SYN-data drops
    
    On paths with firewalls dropping SYN with data or experimental TCP options,
    Fast Open connections will have experience SYN timeout and bad performance.
    The solution is to track such incidents in the cookie cache and disables
    Fast Open temporarily.
    
    Since only the original SYN includes data and/or Fast Open option, the
    SYN-ACK has some tell-tale sign (tcp_rcv_fastopen_synack()) to detect
    such drops. If a path has recurring Fast Open SYN drops, Fast Open is
    disabled for 2^(recurring_losses) minutes starting from four minutes up to
    roughly one and half day. sendmsg with MSG_FASTOPEN flag will succeed but
    it behaves as connect() then write().
    
    Signed-off-by: Yuchung Cheng <ycheng@google.com>
    Acked-by: Eric Dumazet <edumazet@google.com>
    Signed-off-by: David S. Miller <davem@davemloft.net>

diff --git a/include/net/tcp.h b/include/net/tcp.h
index c025810..e07878d 100644
--- a/include/net/tcp.h
+++ b/include/net/tcp.h
@@ -409,9 +409,11 @@ extern bool tcp_peer_is_proven(struct request_sock *req, struct dst_entry *dst,
 extern bool tcp_remember_stamp(struct sock *sk);
 extern bool tcp_tw_remember_stamp(struct inet_timewait_sock *tw);
 extern void tcp_fastopen_cache_get(struct sock *sk, u16 *mss,
-				   struct tcp_fastopen_cookie *cookie);
+				   struct tcp_fastopen_cookie *cookie,
+				   int *syn_loss, unsigned long *last_syn_loss);
 extern void tcp_fastopen_cache_set(struct sock *sk, u16 mss,
-				   struct tcp_fastopen_cookie *cookie);
+				   struct tcp_fastopen_cookie *cookie,
+				   bool syn_lost);
 extern void tcp_fetch_timewait_stamp(struct sock *sk, struct dst_entry *dst);
 extern void tcp_disable_fack(struct tcp_sock *tp);
 extern void tcp_close(struct sock *sk, long timeout);
diff --git a/net/ipv4/tcp_input.c b/net/ipv4/tcp_input.c
index 38b6a81..c49a4fc 100644
--- a/net/ipv4/tcp_input.c
+++ b/net/ipv4/tcp_input.c
@@ -5652,6 +5652,7 @@ static bool tcp_rcv_fastopen_synack(struct sock *sk, struct sk_buff *synack,
 	struct tcp_sock *tp = tcp_sk(sk);
 	struct sk_buff *data = tcp_write_queue_head(sk);
 	u16 mss = tp->rx_opt.mss_clamp;
+	bool syn_drop;
 
 	if (mss == tp->rx_opt.user_mss) {
 		struct tcp_options_received opt;
@@ -5664,7 +5665,14 @@ static bool tcp_rcv_fastopen_synack(struct sock *sk, struct sk_buff *synack,
 		mss = opt.mss_clamp;
 	}
 
-	tcp_fastopen_cache_set(sk, mss, cookie);
+	/* The SYN-ACK neither has cookie nor acknowledges the data. Presumably
+	 * the remote receives only the retransmitted (regular) SYNs: either
+	 * the original SYN-data or the corresponding SYN-ACK is lost.
+	 */
+	syn_drop = (cookie->len <= 0 && data &&
+		    inet_csk(sk)->icsk_retransmits);
+
+	tcp_fastopen_cache_set(sk, mss, cookie, syn_drop);
 
 	if (data) { /* Retransmit unacked data in SYN */
 		tcp_retransmit_skb(sk, data);
diff --git a/net/ipv4/tcp_metrics.c b/net/ipv4/tcp_metrics.c
index d02ff37..99779ae 100644
--- a/net/ipv4/tcp_metrics.c
+++ b/net/ipv4/tcp_metrics.c
@@ -32,6 +32,8 @@ enum tcp_metric_index {
 
 struct tcp_fastopen_metrics {
 	u16	mss;
+	u16	syn_loss:10;		/* Recurring Fast Open SYN losses */
+	unsigned long	last_syn_loss;	/* Last Fast Open SYN loss */
 	struct	tcp_fastopen_cookie	cookie;
 };
 
@@ -125,6 +127,7 @@ static void tcpm_suck_dst(struct tcp_metrics_block *tm, struct dst_entry *dst)
 	tm->tcpm_ts = 0;
 	tm->tcpm_ts_stamp = 0;
 	tm->tcpm_fastopen.mss = 0;
+	tm->tcpm_fastopen.syn_loss = 0;
 	tm->tcpm_fastopen.cookie.len = 0;
 }
 
@@ -644,7 +647,8 @@ bool tcp_tw_remember_stamp(struct inet_timewait_sock *tw)
 static DEFINE_SEQLOCK(fastopen_seqlock);
 
 void tcp_fastopen_cache_get(struct sock *sk, u16 *mss,
-			    struct tcp_fastopen_cookie *cookie)
+			    struct tcp_fastopen_cookie *cookie,
+			    int *syn_loss, unsigned long *last_syn_loss)
 {
 	struct tcp_metrics_block *tm;
 
@@ -659,14 +663,15 @@ void tcp_fastopen_cache_get(struct sock *sk, u16 *mss,
 			if (tfom->mss)
 				*mss = tfom->mss;
 			*cookie = tfom->cookie;
+			*syn_loss = tfom->syn_loss;
+			*last_syn_loss = *syn_loss ? tfom->last_syn_loss : 0;
 		} while (read_seqretry(&fastopen_seqlock, seq));
 	}
 	rcu_read_unlock();
 }
 
-
 void tcp_fastopen_cache_set(struct sock *sk, u16 mss,
-			    struct tcp_fastopen_cookie *cookie)
+			    struct tcp_fastopen_cookie *cookie, bool syn_lost)
 {
 	struct tcp_metrics_block *tm;
 
@@ -679,6 +684,11 @@ void tcp_fastopen_cache_set(struct sock *sk, u16 mss,
 		tfom->mss = mss;
 		if (cookie->len > 0)
 			tfom->cookie = *cookie;
+		if (syn_lost) {
+			++tfom->syn_loss;
+			tfom->last_syn_loss = jiffies;
+		} else
+			tfom->syn_loss = 0;
 		write_sequnlock_bh(&fastopen_seqlock);
 	}
 	rcu_read_unlock();
diff --git a/net/ipv4/tcp_output.c b/net/ipv4/tcp_output.c
index 8869328..c5cfd5e 100644
--- a/net/ipv4/tcp_output.c
+++ b/net/ipv4/tcp_output.c
@@ -2860,10 +2860,19 @@ static int tcp_send_syn_data(struct sock *sk, struct sk_buff *syn)
 {
 	struct tcp_sock *tp = tcp_sk(sk);
 	struct tcp_fastopen_request *fo = tp->fastopen_req;
-	int space, i, err = 0, iovlen = fo->data->msg_iovlen;
+	int syn_loss = 0, space, i, err = 0, iovlen = fo->data->msg_iovlen;
 	struct sk_buff *syn_data = NULL, *data;
+	unsigned long last_syn_loss = 0;
+
+	tcp_fastopen_cache_get(sk, &tp->rx_opt.mss_clamp, &fo->cookie,
+			       &syn_loss, &last_syn_loss);
+	/* Recurring FO SYN losses: revert to regular handshake temporarily */
+	if (syn_loss > 1 &&
+	    time_before(jiffies, last_syn_loss + (60*HZ << syn_loss))) {
+		fo->cookie.len = -1;
+		goto fallback;
+	}
 
-	tcp_fastopen_cache_get(sk, &tp->rx_opt.mss_clamp, &fo->cookie);
 	if (fo->cookie.len <= 0)
 		goto fallback;
 
