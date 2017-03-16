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

	if (-1 == bind (listenfd, (struct sockaddr*)&server_addr, sizeof (server_addr)))
		ERR_EXIT ("bind");

	if (-1 == listen (listenfd, SOMAXCONN))
		ERR_EXIT ("listen");
	
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof (client_addr);
	int conn = accept (listenfd, (struct sockaddr*)&client_addr, &client_len);
	if (-1 == conn)
		ERR_EXIT ("accept");

	printf ("ip = %s, port = %u", inet_ntoa (client_addr.sin_addr), ntohs (client_addr.sin_port));

	char receive_buf[1024] = {0};
	while (1)
	{	
		memset (receive_buf, 0, sizeof (receive_buf));
		int ret = read (conn, receive_buf, sizeof (receive_buf));
		write (conn, receive_buf, ret);
		fputs (receive_buf, stdout);
	}

	close (listenfd);

	return 0;


}
