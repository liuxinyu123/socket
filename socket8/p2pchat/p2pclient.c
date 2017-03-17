#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


#define  ERR_EXIT(m)\
do {\
	perror (m);\
	exit (EXIT_FAILURE);\
} while (0)

void do_read (int n);
void do_write (int n);

const char conn_addr[] = "127.0.0.1";

int main (int argc, char *argv[])
{
	int sock = socket (PF_INET, SOCK_STREAM, 0);

	if (-1 == sock)
		ERR_EXIT ("socket");

	struct sockaddr_in connect_addr;
	connect_addr.sin_family = AF_INET;
	connect_addr.sin_addr.s_addr = htonl (inet_addr (conn_addr));
	connect_addr.sin_port = htons (8888);

	if (-1 == connect (sock, (struct sockaddr*)&connect_addr, sizeof (connect_addr)))
		ERR_EXIT ("connect");


}

void do_read (int n)
{

}

void do_write (int n)
{

}
