#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int arr[] = {1, 2, 3, 4, 1, 2, 7};
	int arr_size = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	if (pipe(fd) == -1)
		return 1;

	int id = fork();
	if (id == -1)
		return 2;
	
	if (id == 0)
	{
		start = 0;
		end = arr_size / 2;
	}
	else
	{
		start = arr_size / 2;
		end = arr_size;
	}

	int sum = 0;
	int i;
	for (i = start; i < end; i++)
	{
		sum += arr[i];
	}
	printf("Calculated parial sum : %d\n", sum);

	if (id == 0)
	{
		close(fd[0]);
		write(fd[1], &sum, sizeof(int));
		close(fd[1]);
	}
	else
	{
		int sum_from_child;
		close(fd[1]);
		read(fd[0], &sum_from_child, sizeof(int));
		close(fd[0]);

		int total_sum = sum + sum_from_child;
		printf("Total sum is %d\n", total_sum);
		wait(0);
	}
	return 0;
}