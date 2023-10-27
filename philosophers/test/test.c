#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *test(char **arr)
{
	printf("%s\n", arr[0]);
	printf("%s\n", arr[1]);
	return NULL;
}

int main()
{
	pthread_t t;
	char **a = (char **)malloc(sizeof(char *) * 3);
	a[2] = NULL;
	a[0] = (char *)malloc(sizeof(char) * 3);
	a[1] = (char *)malloc(sizeof(char) * 3);
	a[0] = "ab";
	a[1] = "cd";

	pthread_create(&t, NULL, (void *)test, a);
	pthread_join(t, NULL);

	return 0;
}