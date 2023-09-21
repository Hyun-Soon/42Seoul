#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	int p1[2]; //child -> parent
	int p2[2]; //parent -> child
	if (pipe(p1) == -1)
		return 1;
	if (pipe(p2) == -1)
		return 1;
	int pid = fork();
	if (pid == -1)
		return 2;
	if (pid == 0)
	{
		//child
		close(p1[0]);
		close(p2[1]);
		int x;
		if (read(p2[0], &x, sizeof(int)) == -1)
			return 3;
		printf("child Received %d\n", x);
		x *= 4;
		if (write(p1[1], &x, sizeof(x)) == -1)
			return 4;
		printf("child Wrote %d\n", x);
		close(p1[1]);
		close(p2[0]);
	}
	else
	{
		//parent
		close(p1[1]);
		close(p2[0]);
		srand(time(NULL));
		int y = rand() % 10;
		if (write(p2[1], &y, sizeof(y)) == -1)
			return 5;
		printf("parent Wrote %d\n", y);
		if (read(p1[0], &y, sizeof(y)) == -1)
			return 6;
		printf("parent Result is %d\n", y);
		close(p1[0]);
		close(p2[1]);
	}
	return 0;
}