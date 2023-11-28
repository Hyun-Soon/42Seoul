/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:19:10 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/28 22:30:04 by hyuim            ###   ########.fr       */
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
			break ;
		}
	}
	if (pid == -1)
		exit(4);
	if (pid == 0)
		routine(bundle);
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
		if (WIFEXITED(status) == 1) //starve
		{
			kill(0, SIGINT);
			break ;
		}
	}
}
