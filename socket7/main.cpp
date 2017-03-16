#include <iostream>
#include <sys/socket.h>

using std::cout;
using std::endl;

int main (int argc, char *argv[])
{
	int listenfd = 0;
	listenfd = socket (PF_INET, SOCK_STREAM, 0);	
	
	if (-1 == listenfd)
		cout << "Socket create failed" << endl;	

	return 0;
}
