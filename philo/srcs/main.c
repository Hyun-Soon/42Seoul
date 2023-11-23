/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:45 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/23 22:32:50 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
#include "../headers/philosophers.h"

long	get_timestamp(t_philo *philo)
{
	struct timeval	s_now;
	long	ret;

	gettimeofday(&s_now, NULL);
	ret = (s_now.tv_sec - philo->bundle->s_start.tv_sec) * 1000 + (s_now.tv_usec / 1000) - (philo->bundle->s_start.tv_usec / 1000);
	return (ret);
}

long	get_time_since(struct timeval s_before_time)
{
	struct timeval	s_now;
	long			ret;

	gettimeofday(&s_now, NULL);
	ret = (s_now.tv_sec - s_before_time.tv_sec) * 1000 + (s_now.tv_usec / 1000) - (s_before_time.tv_usec / 1000);
	return (ret);
}

void	get_left_fork(t_philo *philo)
{
	while(1)
	{
		pthread_mutex_lock(&philo->bundle->fork_mutexes[philo->id]);
		if (philo->bundle->forks[philo->id])
		{
			philo->bundle->forks[philo->id] = 0;
			pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->id]);
			pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
			if (philo->bundle->sb_dead_or_full == 0)
				printf("%ld	%d has taken a fork\n", get_timestamp(philo), philo->id + 1);
			pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->id]);
		usleep(DT);
	}
}

void	get_right_fork(t_philo *philo)
{
	while(1)
	{
		pthread_mutex_lock(&philo->bundle->fork_mutexes[(philo->id + 1) % philo->bundle->num_of_philos]);
		if (philo->bundle->forks[(philo->id + 1) % philo->bundle->num_of_philos])
		{
			philo->bundle->forks[(philo->id + 1) % philo->bundle->num_of_philos] = 0;
			pthread_mutex_unlock(&philo->bundle->fork_mutexes[(philo->id + 1) % philo->bundle->num_of_philos]);
			pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
			if (philo->bundle->sb_dead_or_full == 0)
				printf("%ld	%d has taken a fork\n", get_timestamp(philo), philo->id + 1);
			pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->bundle->fork_mutexes[(philo->id + 1) % philo->bundle->num_of_philos]);
		usleep(DT);
	}
}

void	set_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->eat_time_mutexes[philo->id]);
	gettimeofday(&philo->s_eat_time, NULL);
	pthread_mutex_unlock(&philo->bundle->eat_time_mutexes[philo->id]);
}

void	optimized_sleep(struct timeval ref_time, int target_time)
{
	long	sleep_time;
	long	u_constant_time;
	int	time_threadhold;
	struct timeval	s_now;

	u_constant_time = target_time * 1000 + ref_time.tv_sec * 1000000 + ref_time.tv_usec;
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

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	if (philo->bundle->sb_dead_or_full == 0)
		printf("%ld	%d is eating\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	set_eat_time(philo);
	optimized_sleep(philo->s_eat_time, philo->bundle->time_to_eat);
	pthread_mutex_lock(&philo->bundle->eat_cnt_mutexes[philo->id]);
	philo->bundle->eating_count[philo->id]++;
	//printf("id : %d, cnt : %d, sb_dead_or_full flag : %d\n", philo->id + 1, philo->bundle->eating_count[philo->id], philo->bundle->sb_dead_or_full); //////
	pthread_mutex_unlock(&philo->bundle->eat_cnt_mutexes[philo->id]);
	philo_put_down_forks(philo);
}

void	philo_sleeping(t_philo *philo)
{
	struct timeval	s_start_sleeping;

	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	if (philo->bundle->sb_dead_or_full == 0)
		printf("%ld	%d is sleeping\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	gettimeofday(&s_start_sleeping, NULL);
	optimized_sleep(s_start_sleeping, philo->bundle->time_to_sleep);
}

void	put_down_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->fork_mutexes[philo->id]);
	philo->bundle->forks[philo->id] = 1;
	pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->id]);
}

void	put_down_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->fork_mutexes[(philo->id + 1) % philo->bundle->num_of_philos]);
	philo->bundle->forks[(philo->id + 1) % philo->bundle->num_of_philos] = 1;
	pthread_mutex_unlock(&philo->bundle->fork_mutexes[(philo->id + 1) % philo->bundle->num_of_philos]);
}

void	philo_put_down_forks(t_philo *philo)
{
	put_down_left(philo);
	put_down_right(philo);
}

void	philo_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	if (philo->bundle->sb_dead_or_full == 0)
		printf("%ld	%d is thinking\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	if (philo->bundle->odd_flag)
		usleep(DT);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id % 2 == 1)
		while (get_time_since(philo->bundle->s_start) < philo->bundle->time_to_eat / 4)
			usleep(philo->bundle->time_to_eat / 8);
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	while (philo->bundle->sb_dead_or_full == 0)
	{
		pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);

		if (philo->id % 2 == 0)
		{
			get_left_fork(philo);
			get_right_fork(philo);
		}
		else
		{
			get_right_fork(philo);
			get_left_fork(philo);
		}
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);

		pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	}
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	return (NULL);
}

void	free_remains(t_bundle *bundle, t_philo *philos)
{
	if (philos)
		free(philos);
	if (bundle->threads)
		free(bundle->threads);
	if (bundle->forks)
		free(bundle->forks);
	if (bundle->fork_mutexes)
		free(bundle->fork_mutexes);
	if (bundle->eat_time_mutexes)
		free(bundle->eat_time_mutexes);
	if (bundle->eating_count)
		free(bundle->eating_count);
	if (bundle->eat_cnt_mutexes)
		free(bundle->eat_cnt_mutexes);
}

void	null_init(t_bundle *bundle)
{
	bundle->threads = NULL;
	bundle->forks = NULL;
	bundle->fork_mutexes = NULL;
	bundle->eat_time_mutexes = NULL;
	bundle->eating_count = NULL;
	bundle->eat_cnt_mutexes = NULL;
}

int	init_bundle(t_bundle *bundle, t_philo *philos, int argc, char **argv)
{
	int atoi_args_ret;

	null_init(bundle);
	bundle->number_of_times_for_each = -1014;
	bundle->sb_dead_or_full = 0;
	bundle->odd_flag = 0;
	if (pthread_mutex_init(&bundle->sb_dead_or_full_mutex, NULL) != 0)
			return (-1);
	atoi_args_ret = atoi_args(bundle, philos, argc, argv);
	if (atoi_args_ret == -1)
		return (-1);
	return (0);
}

void	check_dead_or_full(t_bundle *bundle, t_philo *philos)
{
	int	idx;
	int	full_flag;

	while (bundle->sb_dead_or_full == 0)
	{
		full_flag = 1;
		idx = -1;
		while (++idx < bundle->num_of_philos)
		{
			pthread_mutex_lock(&bundle->eat_time_mutexes[idx]);
			if (get_time_since(philos[idx].s_eat_time) >= bundle->time_to_die)
			{
				pthread_mutex_unlock(&bundle->eat_time_mutexes[idx]);
				pthread_mutex_lock(&bundle->sb_dead_or_full_mutex);
				bundle->sb_dead_or_full = 1;
				pthread_mutex_unlock(&bundle->sb_dead_or_full_mutex);
				print_die_msg(bundle, idx + 1);
				return ;
			}
			else
				pthread_mutex_unlock(&bundle->eat_time_mutexes[idx]);
			
			if (bundle->number_of_times_for_each != -1014)
			{
				pthread_mutex_lock(&bundle->eat_cnt_mutexes[idx]);
				if (bundle->eating_count[idx] < bundle->number_of_times_for_each)
					full_flag = 0;
				pthread_mutex_unlock(&bundle->eat_cnt_mutexes[idx]);
			}
		}

		if (bundle->number_of_times_for_each != -1014 && full_flag)
		{
			pthread_mutex_lock(&bundle->sb_dead_or_full_mutex);
			bundle->sb_dead_or_full = 1;
			pthread_mutex_unlock(&bundle->sb_dead_or_full_mutex);
			return ;
		}

		usleep(DT);
	}
}


void	print_die_msg(t_bundle *bundle, int dead)
{
	printf("%ld	%d died\n", get_time_since(bundle->s_start), dead);
}

int	set_start_time(t_bundle *bundle, t_philo *philos)
{
	int	idx;

	idx = -1;
	if (gettimeofday(&bundle->s_start, NULL) == -1)
	{
		destroy_all_mutexes_and_all_free(bundle, philos);
		return (-1);
	}
	while (++idx < bundle->num_of_philos)
		philos[idx].s_eat_time = bundle->s_start;
	return (0);
}

t_philo	*init_philos(t_bundle *bundle)
{
	int	idx;
	t_philo	*ret;

	ret = (t_philo *)malloc(sizeof(t_philo) * bundle->num_of_philos);
	if (!ret)
		return (NULL);
	idx = -1;
	while (++idx < bundle->num_of_philos)
	{
		ret[idx].id = idx;
		ret[idx].bundle = bundle;
	}
	return (ret);
}

void	destroy_all_mutexes_and_all_free(t_bundle *bundle, t_philo *philos)
{
	int	idx;

	idx = -1;
	free_remains(bundle, philos);
	while (++idx < bundle->num_of_philos)
	{
		pthread_mutex_destroy(&bundle->fork_mutexes[idx]);
		pthread_mutex_destroy(&bundle->eat_time_mutexes[idx]);
	}
	pthread_mutex_destroy(&bundle->sb_dead_or_full_mutex);
}

//TODO :: eating count, 

void	check() /////
{
	system("leaks -q philo");
}

int main(int argc, char**argv)
{
	t_bundle	bundle;
	t_philo		*philos;
	int	idx;

	//atexit(check);
	philos = NULL;
	if (argc < 5)
	{
		printf("Not enough args.\n");
		return (1);
	}
	if (init_bundle(&bundle, philos, argc, argv) == -1)
		return (2);
	philos = init_philos(&bundle);
	if (!philos)
		return (3);
	if (set_start_time(&bundle, philos) == -1)
		return (4);
	idx = -1;
	while (++idx < bundle.num_of_philos)
		pthread_create(&bundle.threads[idx], NULL, routine, (void *)&philos[idx]);

	check_dead_or_full(&bundle, philos);

	idx = -1;
	while (++idx < bundle.num_of_philos)
		pthread_join(bundle.threads[idx], NULL);
	destroy_all_mutexes_and_all_free(&bundle, philos);
	return (0);
}

int	destroy_pre_fork_mutexes(t_bundle *bundle, t_philo *philos, int idx)
{
	int	idx_for_free;

	idx_for_free = -1;
	pthread_mutex_destroy(&bundle->sb_dead_or_full_mutex);
	while (++idx_for_free < idx)
		pthread_mutex_destroy(&bundle->fork_mutexes[idx_for_free]);
	free_remains(bundle, philos);
	return (-1);
}

int	destroy_pre_fork_mutexes_and_eat_time_mutexes(t_bundle *bundle, t_philo *philos, int idx)
{
	int	idx_for_free;

	idx_for_free = -1;
	pthread_mutex_destroy(&bundle->sb_dead_or_full_mutex);
	while (++idx_for_free < idx)
	{
		pthread_mutex_destroy(&bundle->fork_mutexes[idx_for_free]);
		pthread_mutex_destroy(&bundle->eat_time_mutexes[idx_for_free]);
	}
	free_remains(bundle, philos);
	return (-1);
}

int	destroy_all_mutexes(t_bundle *bundle, t_philo *philos, int idx)
{
	int	idx_for_free;

	idx_for_free = -1;
	pthread_mutex_destroy(&bundle->sb_dead_or_full_mutex);
	while (++idx_for_free < idx)
	{
		pthread_mutex_destroy(&bundle->fork_mutexes[idx_for_free]);
		pthread_mutex_destroy(&bundle->eat_time_mutexes[idx_for_free]);
		pthread_mutex_destroy(&bundle->eat_cnt_mutexes[idx_for_free]);
	}
	free_remains(bundle, philos);
	return (-1);
}

int	setting_table(t_bundle *bundle, t_philo *philos)
{
	int	idx;

	bundle->threads = (pthread_t *)malloc(sizeof(pthread_t) * bundle->num_of_philos);
	if (!bundle->threads)
		return (-1);
	bundle->forks = (int *)malloc(sizeof(unsigned int) * bundle->num_of_philos);
	if (!bundle->forks)
		return (-1);
	bundle->fork_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * bundle->num_of_philos);
	if (!bundle->fork_mutexes)
		return (-1);
	bundle->eat_time_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * bundle->num_of_philos);
	if (!bundle->eat_time_mutexes)
		return (-1);
	bundle->eating_count = (int *)malloc(sizeof(int) * bundle->num_of_philos);
	if (!bundle->eating_count)
		return (-1);
	bundle->eat_cnt_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * bundle->num_of_philos);
	if (!bundle->eat_cnt_mutexes)
		return (-1);
	idx = -1;
	if (bundle->num_of_philos % 2 == 1)
		bundle->odd_flag = 1;
	while (++idx < bundle->num_of_philos)
	{
		bundle->forks[idx] = 1;
		if (pthread_mutex_init(&bundle->fork_mutexes[idx], NULL) != 0)
			return (destroy_pre_fork_mutexes(bundle, philos, idx));
		if (pthread_mutex_init(&bundle->eat_time_mutexes[idx], NULL) != 0)
			return (destroy_pre_fork_mutexes_and_eat_time_mutexes(bundle, philos, idx));
		if (pthread_mutex_init(&bundle->eat_cnt_mutexes[idx], NULL) != 0)
			return (destroy_all_mutexes(bundle, philos, idx));
	}
	return (0);
}

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
