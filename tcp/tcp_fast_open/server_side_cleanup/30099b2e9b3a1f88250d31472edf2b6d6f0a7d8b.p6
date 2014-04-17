commit 30099b2e9b3a1f88250d31472edf2b6d6f0a7d8b
Author: Neal Cardwell <ncardwell@google.com>
Date:   Sat Sep 22 17:03:47 2012 +0000

    tcp: TCP Fast Open Server - record retransmits after 3WHS
    
    When recording the number of SYNACK retransmits for servers using TCP
    Fast Open, fix the code to ensure that we copy over the retransmit
    count from the request_sock after we receive the ACK that completes
    the 3-way handshake.
    
    The story here is similar to that of SYNACK RTT
    measurements. Previously we were always doing this in
    tcp_v4_syn_recv_sock(). However, for TCP Fast Open connections
    tcp_v4_conn_req_fastopen() calls tcp_v4_syn_recv_sock() at the time we
    receive the SYN. So for TFO we must copy the final SYNACK retransmit
    count in tcp_rcv_state_process().
    
    Note that copying over the SYNACK retransmit count will give us the
    correct count since, as is mentioned in a comment in
    tcp_retransmit_timer(), before we receive an ACK for our SYN-ACK a TFO
    passive connection does not retransmit anything else (e.g., data or
    FIN segments).
    
    Signed-off-by: Neal Cardwell <ncardwell@google.com>
    Signed-off-by: David S. Miller <davem@davemloft.net>

diff --git a/net/ipv4/tcp_input.c b/net/ipv4/tcp_input.c
index 36e069a..e037697 100644
--- a/net/ipv4/tcp_input.c
+++ b/net/ipv4/tcp_input.c
@@ -5985,6 +5985,8 @@ int tcp_rcv_state_process(struct sock *sk, struct sk_buff *skb,
 				 */
 				if (req) {
 					tcp_synack_rtt_meas(sk, req);
+					tp->total_retrans = req->retrans;
+
 					reqsk_fastopen_remove(sk, req, false);
 				} else {
 					/* Make sure socket is routed, for
