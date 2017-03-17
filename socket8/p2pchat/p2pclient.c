#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>


#define  ERR_EXIT(m)\
do {\
	perror (m);\
	exit (EXIT_FAILURE);\
} while (0)

void handler ();

const char conn_addr[] = "127.0.0.1";

int main (int argc, char *argv[])
{
	int sock = socket (PF_INET, SOCK_STREAM, 0);

	if (-1 == sock)
		ERR_EXIT ("socket");

	struct sockaddr_in connect_addr;
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_addr.s_addr = inet_addr (conn_addr);
	connect_addr.sin_port = htons (8888);

	if (-1 == connect (sock, (struct sockaddr*)&connect_addr, sizeof (connect_addr)))
		ERR_EXIT ("connect");

	pid_t pid;
	pid = fork ();
	if (-1 == pid)
		ERR_EXIT("fork");

	if (0 == pid)//子进程
	{
		char receive_buf[1024] = {0};
		while (1)
		{
			memset (receive_buf, 0, sizeof (receive_buf));
			int ret = read (sock, receive_buf, sizeof (receive_buf));
			if (-1 == ret)
				ERR_EXIT ("read");
			if (0 == ret)
			{
				puts ("peer close\n");
				break;
			}

			fputs (receive_buf, stdout);
		}
		puts ("child close");
		close (sock);
		kill (getppid (), SIGUSR1);
		exit (EXIT_SUCCESS);

	}
	else
	{
		signal (SIGUSR1, handler);
		char send_buf[1024] = {0};
		while (fgets (send_buf, sizeof (send_buf), stdin) != NULL)
		{
			write (sock, send_buf, strlen (send_buf));		
			memset (send_buf, 0, sizeof (send_buf));
		}
		puts ("parent close");
		close (sock);
		exit (EXIT_SUCCESS);
	}

	close (sock);

	return 0;
}

void handler ()
{
	puts ("receive a signal");
	exit (EXIT_SUCCESS);
}
