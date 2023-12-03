/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:19:10 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/03 13:05:28 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	make_philosophers(t_bundle *bundle)
{
	int	idx;
	int	pid;

	idx = -1;
	gettimeofday(&bundle->s_start, NULL);
	bundle->s_eat_time = bundle->s_start;
	while (++idx < bundle->num_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			bundle->id = idx;
			bundle->t_eat_time_sem = \
			make_sem_until_success(bundle->eat_time_sem_name[idx], 1);
			bundle->t_personal_eat_cnt_sem = \
			make_sem_until_success(bundle->personal_eat_cnt_name[idx], 1);
			break ;
		}
	}
	if (pid == -1)
		exit(4);
	if (pid == 0)
		survival(bundle);
}

void	wait_philosophers(t_bundle *bundle)
{
	int	idx;
	int	status;

	idx = -1;
	status = -1;
	while (++idx < bundle->num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			kill(0, SIGINT);
			break ;
		}
	}
}

void	return_forks(t_bundle *bundle)
{
	if (bundle->hold_forks)
		while (bundle->hold_forks--)
			sem_post(bundle->t_semaphore);
}
