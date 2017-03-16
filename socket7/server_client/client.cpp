#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>

using std::cout;
using std::endl;
using std::cerr;

int main (int argc, char *argv[])
{
	int sock = socket (PF_INET, SOCK_STREAM, 0);

	if (-1 == sock)
		cerr << "create socket fail" << endl;

}
