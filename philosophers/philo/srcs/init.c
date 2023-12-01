/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:57:49 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/01 12:42:13 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

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
	int	atoi_args_ret;

	null_init(bundle);
	bundle->number_of_times_for_each = -1014;
	bundle->sb_dead_or_full = 0;
	bundle->odd_flag = 0;
	bundle->time_to_eat_minus_one = 0;
	if (pthread_mutex_init(&bundle->sb_dead_or_full_mutex, NULL) != 0)
		return (-1);
	atoi_args_ret = atoi_args(bundle, philos, argc, argv);
	if (atoi_args_ret == -1)
		return (-1);
	return (0);
}

t_philo	*init_philos(t_bundle *bundle)
{
	int		idx;
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

int	malloc_bundle_members(t_bundle *bundle)
{
	bundle->threads = (pthread_t *)malloc
		(sizeof(pthread_t) * bundle->num_of_philos);
	if (!bundle->threads)
		return (-1);
	bundle->forks = (int *)malloc(sizeof(unsigned int) * bundle->num_of_philos);
	if (!bundle->forks)
		return (-1);
	bundle->fork_mutexes = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * bundle->num_of_philos);
	if (!bundle->fork_mutexes)
		return (-1);
	bundle->eat_time_mutexes = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * bundle->num_of_philos);
	if (!bundle->eat_time_mutexes)
		return (-1);
	bundle->eating_count = (int *)malloc(sizeof(int) * bundle->num_of_philos);
	if (!bundle->eating_count)
		return (-1);
	bundle->eat_cnt_mutexes = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * bundle->num_of_philos);
	if (!bundle->eat_cnt_mutexes)
		return (-1);
	return (0);
}

int	setting_table(t_bundle *bundle, t_philo *philos)
{
	int	idx;

	if (malloc_bundle_members(bundle) == -1)
		return (-1);
	idx = -1;
	if (bundle->num_of_philos & 1)
	{
		bundle->odd_flag = 1;
		bundle->time_to_eat_minus_one = bundle->time_to_eat - 1;
	}
	while (++idx < bundle->num_of_philos)
	{
		bundle->forks[idx] = 1;
		bundle->eating_count[idx] = 0;
		if (pthread_mutex_init(&bundle->fork_mutexes[idx], NULL) != 0)
			return (destroy_pre_fork_mutexes(bundle, philos, idx));
		if (pthread_mutex_init(&bundle->eat_time_mutexes[idx], NULL) != 0)
			return (destroy_pre_fork_mutexes_and_eat_time_mutexes
				(bundle, philos, idx));
		if (pthread_mutex_init(&bundle->eat_cnt_mutexes[idx], NULL) != 0)
			return (destroy_all_mutexes(bundle, philos, idx));
	}
	return (0);
}
