/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:16:07 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/01 12:50:39 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	put_down_forks(t_bundle *bundle)
{
	sem_post(bundle->t_semaphore);
	down_hold_forks(bundle);
	sem_post(bundle->t_semaphore);
	down_hold_forks(bundle);
}

void	philo_eating(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	sem_wait(bundle->t_eat_time_sem);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	sem_post(bundle->t_eat_time_sem);
	sem_wait(bundle->t_personal_eat_cnt_sem);
	if (time_since_last_meal < bundle->time_to_die
		&& bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		sem_post(bundle->t_personal_eat_cnt_sem);
		sem_wait(bundle->t_print_semaphore);
		printf("%ld	%d is eating\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->t_print_semaphore);
		sem_wait(bundle->t_personal_eat_cnt_sem);
		bundle->eat_cnt++;
		sem_post(bundle->t_personal_eat_cnt_sem);
		bundle->s_eat_time = s_now;
	}
	else
		sem_post(bundle->t_personal_eat_cnt_sem);
	optimized_sleep(s_now, bundle->time_to_eat);
	put_down_forks(bundle);
}

void	philo_sleeping(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	sem_wait(bundle->t_eat_time_sem);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	sem_post(bundle->t_eat_time_sem);
	sem_wait(bundle->t_personal_eat_cnt_sem);
	if (time_since_last_meal < bundle->time_to_die
		&& bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		sem_post(bundle->t_personal_eat_cnt_sem);
		sem_wait(bundle->t_print_semaphore);
		printf("%ld	%d is sleeping\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->t_print_semaphore);
	}
	else
		sem_post(bundle->t_personal_eat_cnt_sem);
	optimized_sleep(s_now, bundle->time_to_sleep);
}

void	philo_thinking(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	sem_wait(bundle->t_eat_time_sem);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	sem_post(bundle->t_eat_time_sem);
	sem_wait(bundle->t_personal_eat_cnt_sem);
	if (time_since_last_meal < bundle->time_to_die
		&& bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		sem_post(bundle->t_personal_eat_cnt_sem);
		sem_wait(bundle->t_print_semaphore);
		printf("%ld	%d is thinking\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->t_print_semaphore);
	}
	else
		sem_post(bundle->t_personal_eat_cnt_sem);
	if (bundle->odd_flag)
		usleep(DT << 1);
}

int	survival(t_bundle *bundle)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitoring, (void *)bundle);
	if (bundle->id & 1)
		optimized_sleep(bundle->s_start, bundle->time_to_die / 4);
	while (1)
	{
		get_forks(bundle);
		philo_eating(bundle);
		philo_sleeping(bundle);
		philo_thinking(bundle);
	}
	exit(3);
}
