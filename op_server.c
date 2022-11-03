#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);



int main(int argc, char * argv[])
{
    
    int serv_sock, clnt_sock;
    char opinfo[BUF_SIZE];
    
    int recv_cnt;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;
    
    if(argc != 2)
    {
        printf("Usage : %s <port>", argv[0]);
        exit(1);
    }
   
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");
    else    
        printf("hello world! ");
    
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    else 
        printf("bind ");

    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");
    else
        printf("bind");
  
    clnt_adr_sz = sizeof(clnt_adr);
    for(int i = 0; i < 5; i++)
    {
       
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

        read(clnt_sock, opinfo, BUF_SIZE -1);

        printf("%s", opinfo);
    }


    close(clnt_sock);
    close(serv_sock);
    return 0;
}



void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}