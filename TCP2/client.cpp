#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>   //

int main(int argc, char ** argv)
{
    int sockfd;       //套接口描述符
    int n;           
    struct sockaddr_in servaddr,cliaddr;  // 套接口信息数据结构
                                          // 服务器地址 客户端地址            

    char sendline[1000];
    char recvline[1000];

    if(argc != 2)
    {
        printf("usage : ./client < IP address >\n");
    }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
    }


    bzero(&servaddr,sizeof(servaddr));   //清空结构体
    servaddr.sin_family = AF_INET;       //协议类型IPV4
    servaddr.sin_port = htons(32000);    //端口号（字节序转换）
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); //IP地址（地址格式化）

    /*if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
    printf("inet_pton error for %s\n",argv[1]);
    exit(0);
    }*/

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
    exit(0);
    }


    while(fgets(sendline,1000,stdin) != NULL)   //读 键盘输入内容 到 sendline所指向的内存空间
    {
        sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
        //通过socket传送数据

        n = recvfrom(sockfd,recvline,1000,0,NULL,NULL);
        //通过socket接收数据

        recvline[n] = '\0';
        //字符串结束标志

        fputs(recvline,stdout);
        //显示收到的数据
    }

    close(sockfd);

    return 0;
}
