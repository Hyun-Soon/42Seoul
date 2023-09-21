#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
	int fd[2];
	if (pipe(fd) == -1)
		return 1;

	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	
	if (pid1 == 0)
	{
		//child process
		char *argv[] = {"ls", "-l", NULL};
		char *envp[] = {NULL};
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve("/bin/ls", argv, envp);
		exit(1);
	}
	
	int pid2 = fork();
	if (pid2 < 0)
		return 3;

	if (pid2 == 0)
	{
		//child process 2 (grep)
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		char *argv[] = {"grep", "main", NULL};
		char *envp[] = {NULL};
		execve("/usr/bin/grep", argv, envp);
	}
	
	close(fd[1]);
	//close(fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
}