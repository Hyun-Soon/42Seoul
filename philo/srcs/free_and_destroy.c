/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:01:16 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/23 23:29:08 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

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

int	destroy_all_mutexes_and_all_free(t_bundle *bundle, t_philo *philos)
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
	return (-1);
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
