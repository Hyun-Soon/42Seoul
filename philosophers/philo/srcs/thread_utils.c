/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 13:34:44 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/04 19:26:02 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosophers.h"

void	all_pthreads_create(t_bundle *bundle, t_philo *philos, int idx)
{
	while (++idx < bundle->num_of_philos)
		pthread_create(&bundle->threads[idx],
			NULL, routine, (void *)&philos[idx]);
}

void	all_pthreads_join(t_bundle *bundle, int idx)
{
	while (++idx < bundle->num_of_philos)
		pthread_join(bundle->threads[idx], NULL);
}

void	philo_get_forks(t_philo *philo)
{
	if (philo->id & 1)
	{
		get_right_fork(philo);
		get_left_fork(philo);
	}
	else
	{
		get_left_fork(philo);
		get_right_fork(philo);
	}
}
