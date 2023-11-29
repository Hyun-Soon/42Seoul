#include <stdio.h>

int main()
{
	int idx = 0;
	while (++idx <= 200)
		printf("idx : %d, char : %c\n", idx, idx);

	return 0;
}