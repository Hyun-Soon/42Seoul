#include <stdio.h>

int main(int argc, char **argv)
{
	int	arr[argc - 1];
	int	arr2[0];
	(void)argv;

	arr[0] = 3;
	arr[1] = 4;
	arr[2] = 5;
	printf("%d\n", argc - 1);
	printf("%d\n", arr[0]);
	printf("%d\n", arr[1]);
	printf("%d\n\n", arr[2]);


	arr2[0] = 123;
	arr2[1] = 456;
	printf("%d\n", arr2[0]);
	printf("%d\n", arr2[1]);
	return 0;
}