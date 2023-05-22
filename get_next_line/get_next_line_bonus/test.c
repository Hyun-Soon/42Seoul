#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>


int main()
{
	char buf[3];
	int fd = open("test.txt", O_RDONLY);
	int ret = read(fd, buf, 0);
	printf("%d\n", ret);
	return 0;
}
