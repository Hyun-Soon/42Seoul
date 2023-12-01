/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:51:14 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/01 16:33:29 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

long	get_timestamp(t_philo *philo)
{
	struct timeval	s_now;
	long			ret;

	gettimeofday(&s_now, NULL);
	ret = (s_now.tv_sec - philo->bundle->s_start.tv_sec) * 1000
		+ (s_now.tv_usec / 1000) - (philo->bundle->s_start.tv_usec / 1000);
	return (ret);
}

long	get_time_since(struct timeval s_before_time)
{
	struct timeval	s_now;
	long			ret;

	gettimeofday(&s_now, NULL);
	ret = (s_now.tv_sec - s_before_time.tv_sec) * 1000
		+ (s_now.tv_usec / 1000) - (s_before_time.tv_usec / 1000);
	return (ret);
}

void	set_eat_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->bundle->eat_time_mutexes[philo->id]);
	gettimeofday(&philo->s_eat_time, NULL);
	pthread_mutex_unlock(&philo->bundle->eat_time_mutexes[philo->id]);
}

void	optimized_sleep(t_philo *philo,
	struct timeval ref_time, int target_time)
{
	long			sleep_time;
	long			u_constant_time;
	struct timeval	s_now;

	u_constant_time = target_time * 1000
		+ ref_time.tv_sec * 1000000 + ref_time.tv_usec;
	gettimeofday(&s_now, NULL);
	sleep_time = u_constant_time - s_now.tv_sec * 1000000 - s_now.tv_usec;
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	while (sleep_time > 0 && philo->bundle->sb_dead_or_full == 0)
	{
		pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
		if (sleep_time > FDT)
			usleep(sleep_time / 2);
		else
			usleep(DT);
		gettimeofday(&s_now, NULL);
		sleep_time = u_constant_time - s_now.tv_sec * 1000000 - s_now.tv_usec;
		pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	}
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
}

int	set_start_time(t_bundle *bundle, t_philo *philos)
{
	int	idx;

	idx = -1;
	if (gettimeofday(&bundle->s_start, NULL) == -1)
		return (destroy_all_mutexes_and_all_free(bundle, philos));
	while (++idx < bundle->num_of_philos)
		philos[idx].s_eat_time = bundle->s_start;
	return (0);
}
