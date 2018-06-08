#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
    int listenfd,connfd,n,i;          //���������� �ļ�������

    struct sockaddr_in servaddr,cliaddr;   //�������Ϳͻ��� �����ַ

    socklen_t clilen;  //��ַ���ȣ���������

    pid_t childpid;    //���̱�ʶ��

    char mesg[1000];   //���͵�����

    listenfd = socket(AF_INET,SOCK_STREAM,0);   //�����׽ӿ�

    bzero(&servaddr,sizeof(servaddr));   
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(32000);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //��ʾ���������ַ�ĺ�

    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));  
    //��
    //�ﶨIP��ַ���˿ں� ��Ҫ�������׽ӿ���

    listen(listenfd,1024);  //�ȴ��׽ӿڵ�����

    for(;;)  // �����ж���ͻ��˺ͷ�����ͬʱ����
    {
        clilen = sizeof(cliaddr); //ȡ�ͻ��˵�ַ����

        connfd = accept(listenfd,(struct sockaddr *)&cliaddr, &clilen); 
        //�����̣� ���ڴ������ӡ� �ĸ��ͻ��˺ͷ��������ӡ�
        //��������׽ӿ�  ������һ���������׽ӿ�
        //��������״̬ 

        if((childpid = fork()) == 0)
        //�ӽ��̣� �Բ����ķ�ʽ����ͻ��˵���Ϣ
        //���û���������䣬��ô�������Ĵ���ʽΪѭ����ʽ��
        {
            close(listenfd);  //�رռ����׽ӿ�

            for(;;)  //��ʾ�������ͻ��˿���һֱͨ��
            {
                n = recvfrom(connfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&clilen);
                //���տͻ�����Ϣ
                if(n == 0)
                {
                    printf("the client %s is closed\n",inet_ntoa(cliaddr.sin_addr.s_addr));

                    break;
                }

                printf("----------------\n");
                printf("----------------\n");   
                mesg[n] = '\0';
                printf("%s\n",mesg);
                //���ͻ��˷��͵���Ϣ��ʾ�ڷ�������

                for(i = 0; i < n; i++)
                {
                    mesg[i] = toupper(mesg[i]);
                }
                //���յ���Сд��ĸ��ɴ�д��ĸ

                sendto(connfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
                //���������͸��ͻ��˱仯�����Ϣ

            }

            close(connfd);
        }
    }

    close(listenfd);

    return 0;
}
