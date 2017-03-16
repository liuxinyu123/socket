#include <stdio.h>
#include <arpa/inet.h>

int main (int argc, char *argv[])
{
	unsigned int a = 0x12345678;//主机字节序为小端
	unsigned char *p = (unsigned char*) &a;

	printf("%0x %0x %0x %0x\n", p[0], p[1], p[2], p[3]);

	unsigned int b = htonl (a);
	p = (unsigned char*)(&b);
	printf("%0x %0x %0x %0x\n", p[0], p[1], p[2], p[3]);

	unsigned int d = ntohl (b);
	p = (unsigned char*) &d;
	printf("%0x %0x %0x %0x\n", p[0], p[1], p[2], p[3]);

	unsigned short a1 = 0x1234;
	unsigned char *q = (unsigned char*)&a1;
	printf ("%0x %0x\n", q[0], q[1]);

	unsigned short b1 = htons (a1);
	q = (unsigned char*)&b1;
	printf ("%0x %0x\n", q[0], q[1]);

	unsigned short c1 = ntohs (b1);
	q = (unsigned char*)&c1;
	printf ("%0x %0x\n", q[0], q[1]);

	return 0;
}
