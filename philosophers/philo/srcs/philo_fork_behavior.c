/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_behavior.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:02:38 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/04 19:08:05 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	get_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	while (philo->bundle->sb_dead_or_full == 0)
	{
		pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
		pthread_mutex_lock(&philo->bundle->fork_mutexes[philo->id]);
		if (philo->bundle->forks[philo->id])
		{
			philo->bundle->forks[philo->id] = 0;
			pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->id]);
			pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
			if (philo->bundle->sb_dead_or_full == 0)
				printf("%ld	%d has taken a fork\n",
					get_timestamp(philo), philo->id + 1);
			pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->id]);
		usleep(DT);
		pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	}
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
}

void	get_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	while (philo->bundle->sb_dead_or_full == 0)
	{
		pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
		pthread_mutex_lock(&philo->bundle->fork_mutexes[philo->right]);
		if (philo->bundle->forks[philo->right])
		{
			philo->bundle->forks[philo->right] = 0;
			pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->right]);
			pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
			if (philo->bundle->sb_dead_or_full == 0)
				printf("%ld	%d has taken a fork\n",
					get_timestamp(philo), philo->id + 1);
			pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->right]);
		usleep(DT);
		pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	}
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
}

void	put_down_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->fork_mutexes[philo->id]);
	philo->bundle->forks[philo->id] = 1;
	pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->id]);
}

void	put_down_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->fork_mutexes[philo->right]);
	philo->bundle->forks[(philo->id + 1) % philo->bundle->num_of_philos] = 1;
	pthread_mutex_unlock(&philo->bundle->fork_mutexes[philo->right]);
}

void	philo_put_down_forks(t_philo *philo)
{
	put_down_left(philo);
	put_down_right(philo);
}
