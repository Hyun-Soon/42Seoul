#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int forks = 4;
	sem_t *semaphore;
	sem_unlink("sem");
	semaphore = sem_open("sem", O_CREAT | O_EXCL | O_RDWR, 0660, forks);
	//sem_wait(semaphore);
	//printf("pick 1\n");
	//sem_wait(semaphore);
	//printf("pick 2\n");
	//sem_wait(semaphore);
	//printf("pick 3\n");
	//sem_wait(semaphore);
	//printf("pick 4\n");
	//sem_wait(semaphore);
	//printf("pick 5\n");

	int pid;

	for (int i = 0; i < forks; i++)
	{
		pid = fork();
		if (pid == 0)
			break;
	}

	if (pid == 0)
	{
		sem_wait(semaphore);
		usleep(10000);
		printf("wow1!!\n");
		//usleep(10000);
		//sem_post(semaphore);
		sem_wait(semaphore);
		printf("wow2!!\n");
	}

	//sem_post(semaphore);
	//sem_post(semaphore);
	//sem_post(semaphore);
	//sem_post(semaphore);
	//sem_post(semaphore);
	if (pid == 0)
		printf("end\n");
	if (pid)
		for (int i = 0; i < forks; i++)
			wait(NULL);
	return 0;
}
