all:oobrecv oobsend
oobrecv:oobrecv.c common.c
	gcc -o oobrecv oobrecv.c common.c 
oobsend:oobsend.c common.c
	gcc -o oobsend oobsend.c common.c 
clean:
	rm oobrecv oobsend -rf
