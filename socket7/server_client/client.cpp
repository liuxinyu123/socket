#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <cstdio>

using std::cout;
using std::endl;
using std::cerr;

int main (int argc, char *argv[])
{
	int sock = socket (PF_INET, SOCK_STREAM, 0);

	if (-1 == sock)
		cerr << "create socket fail" << endl;
	struct sockaddr_in connaddr;
	connaddr.sin_family = AF_INET;
	connaddr.sin_port = htons (5555);
	connaddr.sin_addr.s_addr = inet_addr ("127.0.0.1");

	if (-1 == connect (sock, (sockaddr*)&connaddr, sizeof (connaddr)))
		cerr << "connect error" << endl;

	char send_buf[1024] = {0};
	char receive_buf[1024] = {0};
	while (fgets (send_buf, sizeof (receive_buf), stdin) != nullptr)
	{
		write (sock, send_buf, strlen (send_buf));
		int ret = read (sock, receive_buf, sizeof (receive_buf));	
		cout << receive_buf << endl;
		std::memset (send_buf, 0, sizeof (send_buf));
		std::memset (receive_buf, 0, sizeof (receive_buf));
	}

	close (sock);

	return 0;
}
