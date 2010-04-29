/* 
 * This program will connect to http server and get sth.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define SERVER_PORT 80 
#define BUFFER_SIZE 4096 
static const char* http_get_head="GET http://127.0.0.1/index.html HTTP/1.1\n"
"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, */*\n"
"Accept-Language: zh-cn\n"
"User-Agent:iPanelBrowser/2.0\n"
"Host: www.xxx.com:80\n"
"Connection: close\n\n";

static const char *http_post_head="User-Agent: Tuobao Http 0.1\r\n"
"Cache-Control: no-cache\r\n"
"Content-Type: application/x-www-form-urlencoded\r\n"
"Accept: */*\r\n";

#if 0
int http_post(tuobao_tcpclient *pclient,char *page,char *request,char **response){

        char post[300],host[100],content_len[100];
        char *lpbuf,*ptmp;
        int len=0;

        lpbuf = NULL;
        const char *header2="User-Agent: Tuobao Http 0.1\r\nCache-Control: no-cache\r\nContent-Type: application/x-www-form-urlencoded\r\nAccept: */*\r\n";

        sprintf(post,"POST %s HTTP/1.0\r\n",page);
        sprintf(host,"HOST: %s:%d\r\n",pclient->remote_ip,pclient->remote_port);
        sprintf(content_len,"Content-Length: %d\r\n\r\n",strlen(request));

        len = strlen(post)+strlen(host)+strlen(header2)+strlen(content_len)+strlen(request)+1;
        lpbuf = (char*)malloc(len);
        if(lpbuf==NULL){
                return -1;
        }

        strcpy(lpbuf,post);
        strcat(lpbuf,host);
        strcat(lpbuf,header2);
        strcat(lpbuf,content_len);
        strcat(lpbuf,request);

        if(!pclient->connected){
                tuobao_tcpclient_conn(pclient);
        }

        if(tuobao_tcpclient_send(pclient,lpbuf,len)<0){
                return -1;
        }
        printf("发送请求:\n%s\n",lpbuf);

        /*释放内存*/
        if(lpbuf != NULL) free(lpbuf);
        lpbuf = NULL;

        /*it's time to recv from server*/
        if(tuobao_tcpclient_recv(pclient,&lpbuf,0) <= 0){
                if(lpbuf) free(lpbuf);
                return -2;
        }
        printf("接收响应:\n%s\n",lpbuf);

        /*响应代码,|HTTP/1.0 200 OK|
         *      *从第10个字符开始,第3位
         *           * */
        memset(post,0,sizeof(post));
        strncpy(post,lpbuf+9,3);
        if(atoi(post)!=200){
                if(lpbuf) free(lpbuf);
                return atoi(post);
        }

#endif
int main(int argc, char **argv)
{  
	int fd, size;
	char buf[BUFFER_SIZE];
    struct sockaddr_in http_server_addr;
	socklen_t socklen = sizeof(struct sockaddr_in);

    http_server_addr.sin_family = AF_INET;
    http_server_addr.sin_port = htons(SERVER_PORT);
    inet_aton("127.0.0.1", &http_server_addr.sin_addr);

	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket error!\n");
		exit(EXIT_FAILURE);
	}

	if (connect(fd, (struct sockaddr*)&http_server_addr, socklen) < 0) {
		printf("can't connect to http server error!\n");
		exit(EXIT_FAILURE);
	}

#if 0
    if (send(fd, http_get_head, strlen(http_get_head) + 1, 0) < 0) {
        fprintf(stderr, "send http_protocol_head error\n");
        exit(EXIT_FAILURE);
	}
    FILE *fp = NULL;
    fp = fopen("./index.html", "w+");
    if (!fp) {
        fprintf(stderr, "fopen error\n");
        exit(EXIT_FAILURE);
    }
    bzero(buf, BUFFER_SIZE);
    while ((size = recv(fd, buf, BUFFER_SIZE, 0)) != 0) {
        fwrite(buf, size, 1, fp);
        bzero(buf, BUFFER_SIZE);
    }
    fclose(fp);
#endif
    char post_buf[BUFFER_SIZE];
    FILE *fp = NULL;
    fp = fopen("./client", "r");
    if (!fp) {
        fprintf(stderr, "fopen error\n");
        exit(EXIT_FAILURE);
    }
    bzero(buf, BUFFER_SIZE);
    fread(buf, BUFFER_SIZE, 1, fp);
    fclose(fp);

    sprintf(post_buf, "POST %s HTTP/1.1\r\n", "upact.php");
    char *host = "HOST: 127.0.0.1:80\r\n";
    char *content_len ="Content-Length: 10\r\n\r\n";

    int len = strlen(http_post_head) 
              + strlen(post_buf) 
              + strlen(host) 
              + strlen(content_len) + 1;

    char *lpbuf = (char*)malloc(len);

    strcpy(lpbuf, post_buf);
    strcat(lpbuf, host);
    strcat(lpbuf, http_post_head);
    strcat(lpbuf, content_len);

    if (send(fd, lpbuf, len, 0) == -1) {
        fprintf(stderr, "send error\n");
        exit(EXIT_FAILURE);
    }
	close(fd);
	return 0;
}
