#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define ERR_EXIT(m)\
do { \
	perror (m); \
	exit (EXIT_FAILURE);\
} while (0)

int main (int argc, char *argv[])
{
	int sock = socket (PF_INET, SOCK_STREAM, 0);
	if (-1 == sock)
		ERR_EXIT ("socket");

	struct sockaddr_in connect_addr;
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_port = htons (6666);
	const char *server_addr = "127.0.0.1";
	connect_addr.sin_addr.s_addr = inet_addr (server_addr);

	if (-1 == connect (sock, (struct sockaddr*)&connect_addr, sizeof (connect_addr)))
		ERR_EXIT ("connect");

	char send_buf[1024] = {0};
	char receive_buf[1024] = {0};

	while (fgets (send_buf, sizeof (send_buf), stdin) != NULL)
	{
		write (sock, send_buf, strlen (send_buf));
		int ret = read (sock, receive_buf, sizeof (receive_buf));
		fputs (receive_buf, stdout);
		memset (send_buf, 0, sizeof (send_buf));
		memset (receive_buf, 0, sizeof (receive_buf));
	}

	close (sock);

	return 0;
}
