/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:40 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/27 17:40:35 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	cnt;

	cnt = 0;
	while (*(s + cnt))
		cnt++;
	return (cnt);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc(ft_strlen(s1) + 1);
	if (ret)
	{
		while (*(s1 + i))
		{
			*(ret + i) = *(s1 + i);
			i++;
		}
		*(ret + i) = '\0';
	}
	return (ret);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	ret;

	ret = 0;
	sign = 1;
	if (*str == 0)
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		ret = ret * 10 + (long)(*str - '0');
		if (ret < -2147483648 || ret > 2147483647)
			return (-1);
		str++;
	}
	ret = sign * ret;
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*(src + i) && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	while (*(src + i))
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret)
	{
		while (*(s1 + i))
		{
			*(ret + i) = *(s1 + i);
			i++;
		}
		while (*(s2 + j))
		{
			*(ret + i) = *(s2 + j);
			i++;
			j++;
		}
		*(ret + i) = '\0';
	}
	return (ret);
}

int	make_semaphore(t_bundle *bundle)
{
	char	*temp;
	int		idx;
	int		num_of_forks;

	bundle->sem_name = (char **)malloc(sizeof(char *) * 2);
	if (!bundle->sem_name)
		exit(1);
	bundle->s_semaphore = (sem_t **)malloc(sizeof(sem_t) * 2);
	if (!bundle->s_semaphore)
		exit (1);

	bundle->sem_name[0] = ft_strdup("a");
	bundle->sem_name[1] = ft_strdup("b");

	sem_unlink(bundle->sem_name[0]);
	sem_unlink(bundle->sem_name[1]);
	idx = -1;
	while (++idx < 2)
	{
		if (idx == 0)
			num_of_forks = bundle->num_of_philos / 2 + 1;
		else
			num_of_forks = bundle->num_of_philos / 2;
		bundle->s_semaphore[idx] = sem_open(bundle->sem_name[idx], O_CREAT | O_EXCL, 0660, num_of_forks);
		while (bundle->s_semaphore[idx] == SEM_FAILED)
		{
			temp = bundle->sem_name[idx];
			bundle->sem_name[idx] = ft_strjoin(bundle->sem_name[idx], "sem");
			free(temp);
			sem_unlink(bundle->sem_name[idx]);
			bundle->s_semaphore[idx] = sem_open(bundle->sem_name[idx], O_CREAT | O_EXCL, 0660, num_of_forks);
		}
	}
	return (0);
}

int	init_bundle(t_bundle *bundle, int argc, char **argv)
{
	bundle->num_of_philos = ft_atoi(argv[1]);
	bundle->time_to_die = ft_atoi(argv[2]);
	bundle->time_to_eat = ft_atoi(argv[3]);
	bundle->time_to_sleep = ft_atoi(argv[4]);
	bundle->number_of_times_for_each = -1014;
	bundle->odd_flag = bundle->num_of_philos % 2;
	if (argc == 6)
		bundle->number_of_times_for_each = ft_atoi(argv[5]);
	if (bundle->num_of_philos == -1
		|| bundle->number_of_times_for_each == -1
		|| bundle->time_to_die == -1
		|| bundle->time_to_eat == -1
		|| bundle->time_to_sleep == -1)
	{
		write(2, "arg err.\n", 9);
		return (-1);
	}
	return (0);
}

long	get_time_since(struct timeval s_before_time, struct timeval s_now)
{
	long			ret;

	ret = (s_now.tv_sec - s_before_time.tv_sec) * 1000
		+ (s_now.tv_usec / 1000) - (s_before_time.tv_usec / 1000);
	return (ret);
}

long	get_timestamp(t_bundle *bundle, struct timeval s_now)
{
	long			ret;

	ret = (s_now.tv_sec - bundle->s_start.tv_sec) * 1000
		+ (s_now.tv_usec / 1000) - (bundle->s_start.tv_usec / 1000);
	return (ret);
}

void	optimized_sleep(struct timeval ref_time, int target_time)
{
	long			sleep_time;
	long			u_constant_time;
	int				time_threadhold;
	struct timeval	s_now;

	u_constant_time = target_time * 1000
		+ ref_time.tv_sec * 1000000 + ref_time.tv_usec;
	time_threadhold = 4 * DT;
	gettimeofday(&s_now, NULL);
	sleep_time = u_constant_time - s_now.tv_sec * 1000000 - s_now.tv_usec;
	while (sleep_time > 0)
	{
		if (sleep_time > time_threadhold)
			usleep(sleep_time / 2);
		else
			usleep(DT);
		gettimeofday(&s_now, NULL);
		sleep_time = u_constant_time - s_now.tv_sec * 1000000 - s_now.tv_usec;
	}
}

void	philo_eating(t_bundle *bundle, int *dead_or_full)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	//printf("eat time : %ld\n", time_since_last_meal);
	if (time_since_last_meal < bundle->time_to_die && bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		printf("%ld	%d is eating\n", get_timestamp(bundle, s_now), bundle->id + 1);
		bundle->eat_cnt++;
		gettimeofday(&bundle->s_eat_time, NULL);
	}
	else
		*dead_or_full = bundle->number_of_times_for_each;
	optimized_sleep(bundle->s_eat_time, bundle->time_to_eat);
}

void	philo_sleeping(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	if (time_since_last_meal < bundle->time_to_die && bundle->eat_cnt != bundle->number_of_times_for_each)
		printf("%ld	%d is sleeping\n", get_timestamp(bundle, s_now), bundle->id + 1);
	else
		return ;
	optimized_sleep(s_now, bundle->time_to_sleep);
}

void	philo_thinking(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	if (time_since_last_meal < bundle->time_to_die && bundle->eat_cnt != bundle->number_of_times_for_each)
		printf("%ld	%d is thinking\n", get_timestamp(bundle, s_now), bundle->id + 1);
	if (bundle->odd_flag)
		usleep(DT << 1);
	//TODO :: odd flag & usleep when odd flag is on => usleep should longer than DT that usleep when a fork remain only one. draw time graph
}

void	print_get_fork(t_bundle *bundle, int *dead_or_full)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	if (time_since_last_meal < bundle->time_to_die && bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		//printf("time since last meal : %ld, eat cnt : %d\n", time_since_last_meal, bundle->eat_cnt);
		printf("%ld	%d has taken a fork\n", get_timestamp(bundle, s_now), bundle->id + 1);
		//printf("%ld fork--\n", time_since_last_meal);
	}
	else
		*dead_or_full = bundle->number_of_times_for_each;
}

int	routine(t_bundle *bundle)
{
	int	dead_or_full;
	//int	temp;
	struct timeval s_now;

	dead_or_full = 0;
	if (bundle->id % 2 == 1)
		optimized_sleep(bundle->s_start, bundle->time_to_die / 4);
	//printf("dead_or_full : %d, number of : %d \n", dead_or_full, bundle->number_of_times_for_each);
	while (dead_or_full != bundle->number_of_times_for_each)
	{
		sem_wait(bundle->s_semaphore[0]);
		print_get_fork(bundle, &dead_or_full);
		gettimeofday(&s_now, NULL);

		sem_wait(bundle->s_semaphore[1]);
		gettimeofday(&s_now, NULL);

		print_get_fork(bundle, &dead_or_full);
		philo_eating(bundle, &dead_or_full);
		sem_post(bundle->s_semaphore[1]);
		sem_post(bundle->s_semaphore[0]);

		philo_sleeping(bundle);
		philo_thinking(bundle);
	}
	gettimeofday(&s_now, NULL);
	if (dead_or_full == -1014)
		exit(1);
	exit(0);
}

void	make_philosophers(t_bundle *bundle)
{
	int	idx;
	int	pid;

	idx = -1;
	bundle->eat_cnt = 0;
	gettimeofday(&bundle->s_start, NULL);
	bundle->s_eat_time = bundle->s_start;
	while (++idx < bundle->num_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			bundle->id = idx;
			break ;
		}
	}
	if (pid == -1)
		exit(4);
	if (pid == 0)
		exit(routine(bundle));
}

void	wait_philosophers(t_bundle *bundle)
{
	int	idx;
	int	status;

	idx = -1;
	while (++idx < bundle->num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) == 1)
		{
			kill(0, SIGINT);
			break ;
		}

	}
}

// general = 0
// starve = 1

//TODO ::	free list => 1. bundle.sem_name
//			usleep for every case after sleeping
//			***catch exit status and kill if the dead reason is hunger
//			even if a philo is full, until other all philos are full, the msg should be printed

int main(int argc, char **argv)
{
	t_bundle	bundle;

	if (argc < 5)
	{
		printf("Not enough args.\n");
		return (1);
	}
	if (init_bundle(&bundle, argc, argv) == -1)
		return (2);
	
	if (make_semaphore(&bundle) == -1)
		return (3);

	make_philosophers(&bundle);
	wait_philosophers(&bundle);


	sem_close(bundle.s_semaphore[0]);
	sem_close(bundle.s_semaphore[1]);
	sem_unlink(bundle.sem_name[0]);
	sem_unlink(bundle.sem_name[1]);
	//free_reamins();

	return (0);
}