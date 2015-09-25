#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	FILE* handle = fopen(argv[1], "r");

	int packet_size = strlen("start") + strlen("end\n") + 4*11;
	char buffer[1000];

	fgets(buffer, 1000, handle);
	for(int i=0; i<10; i++)
	{
		printf("%s", buffer);
		fgets(buffer, 1000, handle);
	}

	fclose(handle);
	return 0;
}
