commit 8e4178c1c7b52f7c99f5fd22ef7af6b2bff409e3
Author: Yuchung Cheng <ycheng@google.com>
Date:   Thu Jul 19 06:43:08 2012 +0000

    net-tcp: Fast Open client - receiving SYN-ACK
    
    On receiving the SYN-ACK after SYN-data, the client needs to
    a) update the cached MSS and cookie (if included in SYN-ACK)
    b) retransmit the data not yet acknowledged by the SYN-ACK in the final ACK of
       the handshake.
    
    Signed-off-by: Yuchung Cheng <ycheng@google.com>
    Acked-by: Eric Dumazet <edumazet@google.com>
    Signed-off-by: David S. Miller <davem@davemloft.net>

diff --git a/net/ipv4/tcp_input.c b/net/ipv4/tcp_input.c
index a06bb89..38b6a81 100644
--- a/net/ipv4/tcp_input.c
+++ b/net/ipv4/tcp_input.c
@@ -5646,6 +5646,34 @@ void tcp_finish_connect(struct sock *sk, struct sk_buff *skb)
 	}
 }
 
+static bool tcp_rcv_fastopen_synack(struct sock *sk, struct sk_buff *synack,
+				    struct tcp_fastopen_cookie *cookie)
+{
+	struct tcp_sock *tp = tcp_sk(sk);
+	struct sk_buff *data = tcp_write_queue_head(sk);
+	u16 mss = tp->rx_opt.mss_clamp;
+
+	if (mss == tp->rx_opt.user_mss) {
+		struct tcp_options_received opt;
+		const u8 *hash_location;
+
+		/* Get original SYNACK MSS value if user MSS sets mss_clamp */
+		tcp_clear_options(&opt);
+		opt.user_mss = opt.mss_clamp = 0;
+		tcp_parse_options(synack, &opt, &hash_location, 0, NULL);
+		mss = opt.mss_clamp;
+	}
+
+	tcp_fastopen_cache_set(sk, mss, cookie);
+
+	if (data) { /* Retransmit unacked data in SYN */
+		tcp_retransmit_skb(sk, data);
+		tcp_rearm_rto(sk);
+		return true;
+	}
+	return false;
+}
+
 static int tcp_rcv_synsent_state_process(struct sock *sk, struct sk_buff *skb,
 					 const struct tcphdr *th, unsigned int len)
 {
@@ -5653,9 +5681,10 @@ static int tcp_rcv_synsent_state_process(struct sock *sk, struct sk_buff *skb,
 	struct inet_connection_sock *icsk = inet_csk(sk);
 	struct tcp_sock *tp = tcp_sk(sk);
 	struct tcp_cookie_values *cvp = tp->cookie_values;
+	struct tcp_fastopen_cookie foc = { .len = -1 };
 	int saved_clamp = tp->rx_opt.mss_clamp;
 
-	tcp_parse_options(skb, &tp->rx_opt, &hash_location, 0, NULL);
+	tcp_parse_options(skb, &tp->rx_opt, &hash_location, 0, &foc);
 
 	if (th->ack) {
 		/* rfc793:
@@ -5665,11 +5694,9 @@ static int tcp_rcv_synsent_state_process(struct sock *sk, struct sk_buff *skb,
 		 *	  If SEG.ACK =< ISS, or SEG.ACK > SND.NXT, send
 		 *        a reset (unless the RST bit is set, if so drop
 		 *        the segment and return)"
-		 *
-		 *  We do not send data with SYN, so that RFC-correct
-		 *  test reduces to:
 		 */
-		if (TCP_SKB_CB(skb)->ack_seq != tp->snd_nxt)
+		if (!after(TCP_SKB_CB(skb)->ack_seq, tp->snd_una) ||
+		    after(TCP_SKB_CB(skb)->ack_seq, tp->snd_nxt))
 			goto reset_and_undo;
 
 		if (tp->rx_opt.saw_tstamp && tp->rx_opt.rcv_tsecr &&
@@ -5781,6 +5808,9 @@ static int tcp_rcv_synsent_state_process(struct sock *sk, struct sk_buff *skb,
 
 		tcp_finish_connect(sk, skb);
 
+		if (tp->syn_fastopen && tcp_rcv_fastopen_synack(sk, skb, &foc))
+			return -1;
+
 		if (sk->sk_write_pending ||
 		    icsk->icsk_accept_queue.rskq_defer_accept ||
 		    icsk->icsk_ack.pingpong) {
