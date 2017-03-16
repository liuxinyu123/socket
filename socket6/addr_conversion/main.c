#include <stdio.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	const char addr[] = "192.168.1.100";
	unsigned int a = inet_addr (addr);

	printf ("%u\n", ntohl(a));

	struct in_addr Saddr;
	Saddr.s_addr = a;

	printf ("%s\n", inet_ntoa (Saddr));

	struct in_addr Saddr1;

	int ret = inet_aton (addr, &Saddr1);
	printf ("%u %d\n", ntohl(Saddr1.s_addr), ret);


	return 0;
}
