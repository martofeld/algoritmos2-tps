#include "tp1.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		printf("Wrong arguments\n");
		return 1;
	}

	return start_wachencoin(argv[1]);
}
