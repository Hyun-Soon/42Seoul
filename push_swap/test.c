#include <stdio.h>

void t(int *arr)
{
	printf("in : %d\n", arr[2]);
	arr[2] = 5;
}

int main()
{
	int arr[3];

	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;

	t(arr);
	printf("out : %d\n", arr[2]);
}