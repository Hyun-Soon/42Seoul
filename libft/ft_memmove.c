#include "libft.h"

void *memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	i = 0;
	while (i != len)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	return (dst);
}

//TODO : test this program.
int main()
{
	return 0;
}