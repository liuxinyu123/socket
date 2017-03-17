#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#define ERR_EXIT(m) \
do { \
	perror (m); \
	exit (EXIT_FAILURE); \
} while (0)

void handler ();

const char *host_addr = "127.0.0.1";

int main (int argc, char *argv[])
{
	int listenfd = socket (PF_INET, SOCK_STREAM, 0);

	if (-1 == listenfd)
		ERR_EXIT("socket");

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;	
	server_addr.sin_addr.s_addr = inet_addr (host_addr);
	server_addr.sin_port = htons (8888);
	
	int on = 1;
	if (-1 == setsockopt (listenfd, SOL_SOCKET,SO_REUSEADDR, &on, sizeof (on)))
			ERR_EXIT("setsockopt");

	if (-1 == bind (listenfd, (struct sockaddr*)&server_addr, sizeof (server_addr)))
		ERR_EXIT("bind");

	if (-1 == listen (listenfd, SOMAXCONN))
		ERR_EXIT("listen");

	struct sockaddr_in peer_addr;
	socklen_t peer_addr_len = sizeof (peer_addr);
	int conn = accept (listenfd, (struct sockaddr*)&peer_addr, &peer_addr_len);
	if (-1 == conn)
		ERR_EXIT("accept");
	printf ("ip: %s, port: %u\n", inet_ntoa (peer_addr.sin_addr), ntohs (peer_addr.sin_port));

	pid_t pid;
	pid = fork ();
	if (-1 == pid)
		ERR_EXIT("fork");
	else if (0 == pid)//子进程
	{
		signal (SIGUSR1, handler);
		char send_buf[1024] = {0};
		while (fgets (send_buf, sizeof (send_buf), stdin) != NULL)
		{
			write (conn, send_buf, strlen (send_buf));
			memset (send_buf, 0, sizeof (send_buf));
		}

		exit (EXIT_SUCCESS);
	}
	else//父进程
	{
		while (1)
		{
			char receive_buf[1024];
			memset (receive_buf, 0, sizeof (receive_buf));
			int ret = read (conn, receive_buf, sizeof (receive_buf));
			if (-1 == ret)
				ERR_EXIT("read");
			if (0 == ret)
			{
				puts ("peer close\n");
				break;
			}	
			fputs (receive_buf, stdout);	
		}	
		
		kill (pid, SIGUSR1);
		exit (EXIT_SUCCESS);
	}

	close (conn);
	close (listenfd);
	return 0;
}


void handler ()
{
	puts ("receive a signal");
	exit (EXIT_SUCCESS);
}
