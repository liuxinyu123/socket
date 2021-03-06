#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define ERR_EXIT(m) \
do { \
		perror (m); \
		exit (EXIT_FAILURE); \
} while (0)
		
void do_service (int n);		


int main (int argc, char *argv[])
{
	int listenfd = socket (PF_INET, SOCK_STREAM, 0);

	if (-1 == listenfd)
		ERR_EXIT ("socket");
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (6666);
	const char *host_addr = "127.0.0.1";
	server_addr.sin_addr.s_addr = inet_addr (host_addr);	
	int on = 1;
	if (-1 == setsockopt (listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on)))
		ERR_EXIT ("setsockopt");

	if (-1 == bind (listenfd, (struct sockaddr*)&server_addr, sizeof (server_addr)))
		ERR_EXIT ("bind");

	if (-1 == listen (listenfd, SOMAXCONN))
		ERR_EXIT ("listen");
	
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof (client_addr);
	

	pid_t pid;
	while (1)
	{
		int conn = accept (listenfd, (struct sockaddr*)&client_addr, &client_len);
		if (-1 == conn)
			ERR_EXIT ("accept");

		printf ("ip = %s, port = %u\n", inet_ntoa (client_addr.sin_addr), ntohs (client_addr.sin_port));
		char walcome[20] = "connect ok";
		write (conn, walcome, strlen (walcome));

		pid = fork ();
		if (-1 == pid)
			ERR_EXIT ("fork");
		else if (0 == pid)
		{
			close (listenfd);//子进程不需要监听套接字
			do_service (conn);
			exit (EXIT_SUCCESS);//返回后销毁
		}
		else
			close (conn);//父进程不需要连接套接字
	
	}


	return 0;


}

void do_service (int n)
{
	char receive_buf[1024] = {0};
	while (1)
	{	
		memset (receive_buf, 0, sizeof (receive_buf));
		int ret = read (n, receive_buf, sizeof (receive_buf));
		if (0 == ret)//	客户端关闭
		{
			puts("client closed\n");
			break;
		}
		else if (-1 == ret)//失败也要退出
			ERR_EXIT ("read");
		write (n, receive_buf, ret);
		fputs (receive_buf, stdout);
	}

}
