#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int listenfd,connfd,n,i;          //监听，连接 文件描述服

    struct sockaddr_in servaddr,cliaddr;   //服务器和客户端 网络地址

    socklen_t clilen;  //地址长度（服务器）

    pid_t childpid;    //进程标识符

    char mesg[1000];   //传送的数据

    listenfd = socket(AF_INET,SOCK_STREAM,0);   //创建套接口

    bzero(&servaddr,sizeof(servaddr));   
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(32000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //表示本地任意地址的宏

    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));  
    //绑定
    //帮定IP地址，端口号 到要监听的套接口上

    listen(listenfd,1024);  //等待套接口的连接

    for(;;)  // 可以有多个客户端和服务器同时连接
    {
        clilen = sizeof(cliaddr); //取客户端地址长度

        connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &clilen); 
        //父进程： 用于创建连接。 哪个客户端和服务器连接。
        //输入监听套接口  返回新一个的链接套接口
        //处于阻塞状态 

        if((childpid = fork()) == 0)
        //子进程： 以并发的方式处理客户端的信息
        //如果没有上下两句，那么服务器的处理方式为循环方式。
        {
            close(listenfd);  //关闭监听套接口

            for(;;)  //表示服务器客户端可以一直通信
            {
                n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
                //接收客户端信息
                if(n == 0)
                {
                    printf("the client %s is closed\n",inet_ntoa(cliaddr.sin_addr.s_addr));

                    break;
                }

                printf("----------------\n");
                printf("----------------\n");   
                mesg[n] = '\0';
                printf("%s\n",mesg);
                //将客户端发送的信息显示在服务器上

                for(i = 0; i < n; i++)
                {
                    mesg[i] = toupper(mesg[i]);
                }
                //将收到的小写字母变成大写字母

                sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
                //服务器发送给客户端变化后的信息

            }

            close(connfd);
        }
    }

    close(listenfd);

    return 0;
}
