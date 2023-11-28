/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:16:07 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/28 21:04:05 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	wake_up_or_die(t_bundle *bundle, long time_left_to_die, struct timeval check_time, int target_time)
{
	if (time_left_to_die < target_time)
	{
		optimized_sleep(check_time, time_left_to_die);
		sem_wait(bundle->s_print_semaphore);
		printf("%ld	%d is died\n", get_timestamp(bundle, check_time), bundle->id);
		exit(1);
	}
	optimized_sleep(check_time, target_time);
}

void	philo_eating(t_bundle *bundle, int *dead_or_full)
{
	struct timeval	s_now;
	long			time_since_last_meal;
	long			time_left_to_die;

	gettimeofday(&s_now, NULL);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	if (time_since_last_meal < bundle->time_to_die
		&& bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		sem_wait(bundle->s_print_semaphore);
		printf("%ld	%d is eating\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->s_print_semaphore);
		bundle->eat_cnt++;
		gettimeofday(&bundle->s_eat_time, NULL);
	}
	else
		*dead_or_full = bundle->number_of_times_for_each;

	//time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	time_left_to_die = bundle->time_to_die - time_since_last_meal;
	wake_up_or_die(bundle, time_left_to_die, s_now, bundle->time_to_eat);

	sem_post(bundle->s_semaphore[1]);
	sem_post(bundle->s_semaphore[0]);
}

void	philo_sleeping(t_bundle *bundle, int *dead_or_full)
{
	struct timeval	s_now;
	long			time_since_last_meal;
	long			time_left_to_die;

	gettimeofday(&s_now, NULL);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	if (time_since_last_meal < bundle->time_to_die
		&& bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		sem_wait(bundle->s_print_semaphore);
		printf("%ld	%d is sleeping\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->s_print_semaphore);
	}
	else
		*dead_or_full = bundle->number_of_times_for_each;
	//time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	time_left_to_die = bundle->time_to_die - time_since_last_meal;
	wake_up_or_die(bundle, time_left_to_die, s_now, bundle->time_to_sleep);
	//optimized_sleep(s_now, bundle->time_to_sleep);
}

void	philo_thinking(t_bundle *bundle, int *dead_or_full)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	if (time_since_last_meal < bundle->time_to_die
		&& bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		sem_wait(bundle->s_print_semaphore);
		printf("%ld	%d is thinking\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->s_print_semaphore);
	}
	else
		*dead_or_full = bundle->number_of_times_for_each;
	if (bundle->odd_flag)
		usleep(DT << 1);
}

int	routine(t_bundle *bundle)
{
	int				dead_or_full;
	struct timeval	s_now;

	dead_or_full = 0;
	if (bundle->id % 2 == 1)
		optimized_sleep(bundle->s_start, bundle->time_to_die / 4);
	while (dead_or_full != bundle->number_of_times_for_each)
	{
		get_first_fork(bundle, &dead_or_full);
		get_second_fork(bundle, &dead_or_full);
		philo_eating(bundle, &dead_or_full);
		philo_sleeping(bundle, &dead_or_full);
		philo_thinking(bundle, &dead_or_full);
	}
	if (dead_or_full == -1014)
	{
		printf("I'm not full %d. eat cnt : %d\n", bundle->id + 1, bundle->eat_cnt);
		sem_wait(bundle->s_print_semaphore);
		gettimeofday(&s_now, NULL);
		printf("%ld	%d is died\n", get_timestamp(bundle, s_now), bundle->id);
		exit(1);
	}
	printf("I'm full %d. eat cnt : %d\n", bundle->id + 1, bundle->eat_cnt);
	exit(0);
}
