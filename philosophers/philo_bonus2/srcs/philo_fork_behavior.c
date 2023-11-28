/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_behavior.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:17:11 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/28 23:39:55 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	exit_routine(t_bundle *bundle)
{
	struct timeval	s_now;
	
	if (bundle->eat_cnt == bundle->number_of_times_for_each)
	{
		printf("case 0\n"); //
		exit(0);
	}
	sem_wait(bundle->s_print_semaphore);
	gettimeofday(&s_now, NULL);
	printf("%ld	%d is died\n", get_timestamp(bundle, s_now), bundle->id + 1);
	printf("case 1\n"); //
	exit(1);
}

void	print_get_forks(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;

	gettimeofday(&s_now, NULL);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	if (time_since_last_meal < bundle->time_to_die
		&& bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		sem_wait(bundle->s_print_semaphore);
		printf("%ld	%d has taken a fork\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->s_print_semaphore);
	}
	else
		exit_routine(bundle);
}

void	get_forks(t_bundle *bundle)
{
	sem_wait(bundle->s_semaphore);
	sem_wait(bundle->s_semaphore);
	print_get_forks(bundle);
}

//void	get_first_fork(t_bundle *bundle, int *dead_or_full)
//{
//	sem_wait(bundle->s_semaphore[0]);
//	print_get_fork(bundle, dead_or_full);
//}

//void	get_second_fork(t_bundle *bundle, int *dead_or_full)
//{
//	sem_wait(bundle->s_semaphore[1]);
//	print_get_fork(bundle, dead_or_full);
//}

