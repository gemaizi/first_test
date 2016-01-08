/*************************************************************************
> File Name: echo_select_server.c
> Author: xjhznick
> Mail: xjhznick@gmail.com
> Created Time: 2015��03��26�� ������ 14ʱ03��40��
> Description:ʹ��select����ʵ��I/O���÷�������
************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/select.h>

#include "Parser.h"
void error_handling(char *message);

#define BUFF_SIZE 32

int main(int argc, char *argv[])
{
	int server_sock;
	int client_sock;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_size;

	char buff[BUFF_SIZE];
	fd_set reads, reads_init;
	struct timeval timeout, timeout_init;

	int str_len, i, fd_max, fd_num;

	if (argc != 2)
	{ //����������������������һ���������˿ں�
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	//����socket���������׽���
	server_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (-1 == server_sock)
	{
		error_handling("socket() error.");
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(atoi(argv[1]));

	//����bind��������IP��ַ�Ͷ˿ں�
	if (-1 == bind(server_sock, (struct sockaddr*)&server_addr,
		sizeof(server_addr)))
	{
		error_handling("bind() error");
	}

	//�����˿ڵ���������,��������ȴ�����sizeΪ5
	if (-1 == listen(server_sock, 5))
	{
		error_handling("listen() error");
	}

	//register fd_set var
	FD_ZERO(&reads_init);
	FD_SET(server_sock, &reads_init);//monitor socket: server_sock
	FD_SET(0, &reads_init);// stdin also works
	fd_max = server_sock;
	//
	timeout_init.tv_sec = 5;
	timeout_init.tv_usec = 0;

	while (1)
	{
		//����select֮�󣬳������仯���ļ���������Ӧ��bit����������λ��0���������ñ����ֵ��ͨ������ʹ��
		reads = reads_init;
		//����select֮��timeval��Աֵ����Ϊ��ʱǰʣ���ʱ�䣬���ʹ��ʱҲ��Ҫÿ���ó�ֵ���³�ʼ��
		timeout = timeout_init;
		fd_num = select(fd_max + 1, &reads, NULL, NULL, &timeout);
		if (fd_num < 0)
		{
			fputs("Error select()!", stderr);
			break;
		}
		else if (fd_num == 0)
		{
			puts("Time-out!");
			continue;
		}
		for (i = 0; i <= fd_max; i++)
		{
			if (FD_ISSET(i, &reads))
			{
				if (i == server_sock)
				{//connection request!
					//������������
					client_addr_size = sizeof(client_addr);
					client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
					//accept�����Զ���������I/0 socket
					if (-1 == client_sock)
					{
						error_handling("accept() error");
						//��׳�Բ��ѣ���������˳�
					}
					else
					{
						//ע����ͻ������ӵ��׽����ļ�������
						FD_SET(client_sock, &reads_init);
						if (fd_max < client_sock) fd_max = client_sock;
						printf("Connected client : %d\n", client_sock);
					}
				}
				else
				{//read message!
					str_len = read(i, buff, BUFF_SIZE);
					if (str_len)
					{
					   handleData(str_len,buff);
					}
					else
					{ //close connection
						FD_CLR(i, &reads_init);
						close(i);
						printf("Disconnected client %d!\n", i);
					}
				}//end of i==|!=server_sock
			}//end of if(FD_ISSET)
		}//end of while

	}//end of for

	//�Ͽ����ӣ��ر��׽���
	close(server_sock);

	return 0;
}

void handleData(int bufferSize, char* buffer)
{
	if (bufferSize < 1)
	{
		return;
	}
	
	for (int i = 0; i < bufferSize; i++)
	{
	    
		MAVLinkPacket receivedPacket = mavlink_parse_char(buffer[i] & 0x00ff);
		if (receivedPacket != null)
		{
			printf("receive one packet\n");
		}
	}
}


void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}
