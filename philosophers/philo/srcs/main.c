/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:45 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/04 19:49:09 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	notice_all_philos_full(t_bundle *bundle)
{
	pthread_mutex_lock(&bundle->sb_dead_or_full_mutex);
	bundle->sb_dead_or_full = 1;
	pthread_mutex_unlock(&bundle->sb_dead_or_full_mutex);
}

void	count_eat(t_bundle *bundle, int *full_flag, int idx)
{
	pthread_mutex_lock(&bundle->eat_cnt_mutexes[idx]);
	if (bundle->eating_count[idx] < bundle->number_of_times_for_each)
		*full_flag = 0;
	pthread_mutex_unlock(&bundle->eat_cnt_mutexes[idx]);
}

void	*one_philo_starve(t_philo *philo)
{
	get_left_fork(philo);
	optimized_sleep(philo, philo->bundle->s_start, philo->bundle->time_to_die);
	pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	while (philo->bundle->sb_dead_or_full == 0)
	{
		pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
		usleep(DT);
		pthread_mutex_lock(&philo->bundle->sb_dead_or_full_mutex);
	}
	pthread_mutex_unlock(&philo->bundle->sb_dead_or_full_mutex);
	return (NULL);
}

void	check_dead_or_full(t_bundle *bundle,
			t_philo *philos, int idx, int full_flag)
{
	while (bundle->sb_dead_or_full == 0)
	{
		full_flag = 1;
		idx = -1;
		while (++idx < bundle->num_of_philos)
		{
			pthread_mutex_lock(&bundle->eat_time_mutexes[idx]);
			if (get_time_since(philos[idx].s_eat_time) >= bundle->time_to_die)
			{
				pthread_mutex_unlock(&bundle->eat_time_mutexes[idx]);
				pthread_mutex_lock(&bundle->sb_dead_or_full_mutex);
				bundle->sb_dead_or_full = 1;
				pthread_mutex_unlock(&bundle->sb_dead_or_full_mutex);
				print_die_msg(bundle, idx + 1);
				return ;
			}
			pthread_mutex_unlock(&bundle->eat_time_mutexes[idx]);
			if (bundle->number_of_times_for_each != -1014)
				count_eat(bundle, &full_flag, idx);
		}
		if (bundle->number_of_times_for_each != -1014 && full_flag)
			notice_all_philos_full(bundle);
		usleep(DT);
	}
}

int	main(int argc, char **argv)
{
	t_bundle	bundle;
	t_philo		*philos;

	philos = NULL;
	if (argc < 5)
	{
		printf("Not enough args.\n");
		return (1);
	}
	if (init_bundle(&bundle, philos, argc, argv) == -1)
		return (2);
	philos = init_philos(&bundle);
	if (!philos)
		return (3);
	if (set_start_time(&bundle, philos) == -1)
		return (4);
	all_pthreads_create(&bundle, philos, -1);
	check_dead_or_full(&bundle, philos, -1, 1);
	all_pthreads_join(&bundle, -1);
	destroy_all_mutexes_and_all_free(&bundle, philos);
	return (0);
}
