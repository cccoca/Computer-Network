#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>   //

int main(int argc, char ** argv)
{
    int sockfd;       //�׽ӿ�������
    int n;           
    struct sockaddr_in servaddr,cliaddr;  // �׽ӿ���Ϣ���ݽṹ
                                          // ��������ַ �ͻ��˵�ַ            

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


    bzero(&servaddr,sizeof(servaddr));   //��սṹ��
    servaddr.sin_family = AF_INET;       //Э������IPV4
    servaddr.sin_port = htons(32000);    //�˿ںţ��ֽ���ת����
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); //IP��ַ����ַ��ʽ����

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


    while(fgets(sendline,1000,stdin) != NULL)   //�� ������������ �� sendline��ָ����ڴ�ռ�
    {
        sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
        //ͨ��socket��������

        n = recvfrom(sockfd,recvline,1000,0,NULL,NULL);
        //ͨ��socket��������

        recvline[n] = '\0';
        //�ַ���������־

        fputs(recvline,stdout);
        //��ʾ�յ�������
    }

    close(sockfd);

    return 0;
}
