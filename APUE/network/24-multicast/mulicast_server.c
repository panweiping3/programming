#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERV_PORT 5350
#define MCAST_PORT 5351
#define MCAST_ADDR "224.0.0.251"
#define MCAST_INTERVAL 2
#define LOCAL_ADDR "10.66.17.46"

int main(int argc,char **argv)
{
        int sock_fd;
        struct sockaddr_in mcast_addr,addr_serv,addr_client;
        char send_buf[]="tigerjibo";
        char recv_buf[1024];
        int serv_len,mcast_len;
        int send_num;
        int recv_num;
        int err;
        struct ip_mreq mreq;

        sock_fd = socket(AF_INET,SOCK_DGRAM,0);/*建立套接子*/
        if(sock_fd < 0){
                perror("socket()");
                exit(1);
        } else {
                printf("socket sucefull!\n");
        }

        /*服务器端地址*/
        memset(&addr_serv,0,sizeof(struct sockaddr_in));
        addr_serv.sin_family = AF_INET;
        addr_serv.sin_addr.s_addr = inet_addr(LOCAL_ADDR);
        addr_serv.sin_port = htons(SERV_PORT);
        serv_len = sizeof(struct sockaddr_in);

        /*初始化多播地址*/
        memset(&mcast_addr,0,sizeof(mcast_addr));
        mcast_addr.sin_family = AF_INET;
        mcast_addr.sin_addr.s_addr = inet_addr(MCAST_ADDR);
        mcast_addr.sin_port = htons(MCAST_PORT);

        if(bind(sock_fd,(struct sockaddr*)&addr_serv,serv_len)<0){
                perror("bind");
                exit(1);
        } else {
                printf("bind sucess\n");
        }

        while(1){
                printf("begin send:\n");
                send_num = sendto(sock_fd,send_buf,sizeof(send_buf),0,(struct sockaddr *)&mcast_addr,sizeof(mcast_addr));
                if( send_num  < 0){
                        perror("sendto()");
                        exit(1);
                } else{
                        printf("send sucessful\n");
                }
                sleep(MCAST_INTERVAL);
        }
        close(sock_fd);
        return 0;
}
