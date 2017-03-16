#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

using std::cout;
using std::endl;
using std::cerr;

int main (int argc, char *argv[])
{
	int listenfd = socket (PF_INET, SOCK_STREAM, 0);

	if (-1 == listenfd)
		cerr << "create socket error" << endl;
	struct sockaddr_in serveraddr;
	std::memset(&serveraddr, 0, sizeof (serveraddr));//初始化为0
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons (5555);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	//serveraddr.sin_addr.s_addr = inet_addr ("127.0.0.1");//这三种都可以
	//inet_aton ("127.0.0.1", &serveraddr.sin_addr);
	
	if (-1 == bind (listenfd, (sockaddr*)(&serveraddr), sizeof (serveraddr)))
		cerr << "bind error" << endl;

	if (-1 == listen (listenfd, SOMAXCONN))
		cerr << "listen error" << endl;

	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof (client_addr);
	std::memset (&client_addr, 0, sizeof (client_addr));

	if (-1 == accept (listenfd, (sockaddr*)(&client_addr), &client_len))
		cerr << "accept error" << endl;



}
