/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:05:22 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/04 19:25:28 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	if (philo->bundle->sb_dead_or_full == 0)
		printf("%ld	%d is eating\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	set_eat_time(philo);
	optimized_sleep(philo, philo->s_eat_time, philo->bundle->time_to_eat);
	pthread_mutex_lock(&philo->bundle->eat_cnt_mutexes[philo->id]);
	philo->bundle->eating_count[philo->id]++;
	pthread_mutex_unlock(&philo->bundle->eat_cnt_mutexes[philo->id]);
	philo_put_down_forks(philo);
}

void	philo_sleeping(t_philo *philo)
{
	struct timeval	s_start_sleeping;

	gettimeofday(&s_start_sleeping, NULL);
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	if (philo->bundle->sb_dead_or_full == 0)
		printf("%ld	%d is sleeping\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	optimized_sleep(philo, s_start_sleeping, philo->bundle->time_to_sleep);
}

void	philo_thinking(t_philo *philo)
{
	struct timeval	s_start_think;

	gettimeofday(&s_start_think, NULL);
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	if (philo->bundle->sb_dead_or_full == 0)
		printf("%ld	%d is thinking\n", get_timestamp(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	if (philo->bundle->odd_flag)
		optimized_sleep(philo,
			s_start_think, philo->bundle->time_to_eat_minus_one);
}

void	sleep_for_odd_philos(t_philo *philo)
{
	if (philo->id & 1)
		while (get_time_since(philo->bundle->s_start)
			< philo->bundle->time_to_eat / 4)
			usleep(1000 * philo->bundle->time_to_eat / 8);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->bundle->num_of_philos == 1)
		return (one_philo_starve(philo));
	sleep_for_odd_philos(philo);
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	while (philo->bundle->sb_dead_or_full == 0)
	{
		pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
		philo_get_forks(philo);
		philo_eating(philo);
		philo_sleeping(philo);
		philo_thinking(philo);
		pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	}
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	return (NULL);
}
