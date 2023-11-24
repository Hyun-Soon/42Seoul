# include <sys/time.h>
# include <stdio.h>

typedef struct timeval	t_timeval;

long	get_mtime_diff(t_timeval time, t_timeval ref)
{
	long	diff;

	diff = (time.tv_sec - ref.tv_sec) * 1000
		// + (time.tv_usec / 1000 ) - (ref.tv_usec / 1000);
		+ (time.tv_usec - ref.tv_usec) / 1000;
	return (diff);
}

int main(void)
{
	t_timeval start;
	start.tv_sec = 1000;
	start.tv_usec = 000000;

	t_timeval t1;
	t1.tv_sec = 1000;
	t1.tv_usec = 901000;

	t_timeval t2;
	t2.tv_sec = 1001;
	t2.tv_usec = 100001;

	printf("%lu t1 timestamp \n", get_mtime_diff(t1, start));
	if (get_mtime_diff(t2, t1) >= 200)
		printf("%lu t2 timestamp \n", get_mtime_diff(t2, start));

	printf("apparent timestamp is %lu", get_mtime_diff(t2, start) - get_mtime_diff(t1, start));
	return 0;
}