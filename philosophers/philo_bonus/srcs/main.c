/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:40 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/24 23:20:44 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	atoi_args(t_bundle *bundle, t_philo *philos, int argc, char **argv)
{
	bundle->num_of_philos = ft_atoi(argv[1]);
	bundle->time_to_die = ft_atoi(argv[2]);
	bundle->time_to_eat = ft_atoi(argv[3]);
	bundle->time_to_sleep = ft_atoi(argv[4]);
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
	return (setting_table(bundle, philos));
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

size_t	ft_strlen(const char *s)
{
	int	cnt;

	cnt = 0;
	while (*(s + cnt))
		cnt++;
	return (cnt);
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
	char	*sem;
	int		idx;

	bundle->sem_name = (char *)malloc(sizeof(char) * 4);
	if (bundle->sem_name == NULL)
		return (-1);
	idx = -1;
	sem = "sem";
	while (++idx < 4)
		bundle->sem_name[idx] = sem[idx];

	bundle->s_semaphore = sem_open(bundle->sem_name, O_CREAT | O_RDWR | O_EXCL, 0660, bundle->num_of_philos);
	while (bundle->s_semaphore == SEM_FAILED)
	{
		temp = bundle->sem_name;
		bundle->sem_name = ft_strjoin(bundle->sem_name, "sem");
		free(temp);
		bundle->s_semaphore = sem_open(bundle->sem_name, O_CREAT | O_RDWR | O_EXCL, 0660, bundle->num_of_philos);
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
	if (time_since_last_meal < bundle->time_to_die && bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		printf("%ld	%d is eating\n", get_timestamp(bundle, s_now), bundle->id);
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
		printf("%ld	%d is sleeping\n", get_timestamp(bundle, s_now), bundle->id);
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
		printf("%ld	%d is thinking\n", get_timestamp(bundle, s_now), bundle->id);
	//TODO :: odd flag & usleep when odd flag is on => usleep should longer than DT that usleep when a fork remain only one. draw time graph
}

int	routine(t_bundle *bundle)
{
	int	dead_or_full;

	dead_or_full = 0;
	while (dead_or_full != bundle->number_of_times_for_each)
	{
		while (bundle->s_semaphore == 1)
			usleep(DT);
		sem_wait(bundle->s_semaphore);
		sem_wait(bundle->s_semaphore);
		philo_eating(bundle, &dead_or_full);
		sem_post(bundle->s_semaphore);
		sem_post(bundle->s_semaphore);
		philo_sleeping(bundle);
		philo_thinking();
	}
	pthread_join(bundle->thread, NULL);
	return (dead_or_full);
}

void	make_philosophers(t_bundle *bundle)
{
	int	idx;
	int	pid;

	idx = -1;
	bundle->s_eat_time = bundle->s_start;
	bundle->eat_cnt = 0;
	gettimeofday(&bundle->s_start, NULL);
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

	idx = -1;
	while (idx < bundle->num_of_philos)
		waitpid(-1);
}

//TODO :: free list => 1. bundle.sem_name

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



	sem_close(bundle.sem_name);
	sem_unlink(bundle.sem_name);
	free_reamins();

	return (0);
}