#include <stdio.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	const char addr[] = "192.168.1.100";
	unsigned int a = inet_addr (addr);

	printf ("%u\n", a);

	struct in_addr Saddr;
	Saddr.s_addr = a;

	printf ("%s\n", inet_ntoa (Saddr));


	return 0;
}
