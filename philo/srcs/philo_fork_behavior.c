/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_behavior.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:02:38 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/23 23:04:15 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

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
