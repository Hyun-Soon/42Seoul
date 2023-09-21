#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	int pid = fork();
	if (pid == -1)
		return 1;

	if (pid == 0)
	{
		//child
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	}
	else
	{
		wait(NULL);
		printf("Success!\n");
		printf("Some post processing goes here!\n");
	}
	return 0;
}