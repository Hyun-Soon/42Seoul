#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <signal.h>

int main()
{
	sem_t *sem;

	sem_unlink("asdf");
	sem = sem_open("asdf", O_CREAT | O_EXCL, 0660, 3);

	sem_post(sem);
	sem_wait(sem);
	printf("minus one\n");
	sem_wait(sem);
	printf("minus one\n");
	sem_wait(sem);
	printf("minus one\n");
	sem_wait(sem);
	printf("minus one\n");
	sem_wait(sem);
	printf("minus one\n");

	return 0;
}