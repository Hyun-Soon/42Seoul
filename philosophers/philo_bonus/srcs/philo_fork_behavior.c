/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_behavior.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:17:11 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/28 16:39:35 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	print_get_fork(t_bundle *bundle, int *dead_or_full)
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
		*dead_or_full = bundle->number_of_times_for_each;
}

void	get_first_fork(t_bundle *bundle, int *dead_or_full)
{
	sem_wait(bundle->s_semaphore[0]);
	print_get_fork(bundle, dead_or_full);
}

void	get_second_fork(t_bundle *bundle, int *dead_or_full)
{
	sem_wait(bundle->s_semaphore[1]);
	print_get_fork(bundle, dead_or_full);
}
