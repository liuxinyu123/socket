#include <stdio.h>

int main (int argc, char *argv[])
{
	unsigned long a = 0x12345678;
	unsigned char *p = (unsigned char*)&a;

	printf("%0x %0x %0x %0x\n", p[0], p[1], p[2], p[3]);

	return 0;
}
