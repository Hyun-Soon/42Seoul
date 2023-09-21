#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>

int main()
{
	int pid = fork();
	if (pid == -1)
		return 1;
	
	if (pid == 0)
	{
		int file = open("dup2_result.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1)
			return 2;
		printf("Hello to shell\n");
		int file2 = dup2(file, STDOUT_FILENO);
		printf("Hello to dup2_result.txt\n");
		close(file);
	}
}
