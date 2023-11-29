/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:19:10 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/29 23:21:46 by hyuim            ###   ########.fr       */
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
	//printf("wtf\n");
	//printf("before fork, s_start usec : %d\n", bundle->s_start.tv_usec);
	
	while (++idx < bundle->num_of_philos)
	{
		pid = fork();
		if (pid == 0)
		{ //semaphore는 survival에서 만들기, survival 끝날 때 unlink 및 destroy?(free?)해주기, 
			bundle->id = idx;
			bundle->t_eat_time_sem = make_sem_until_success(bundle->eat_time_sem_name[idx], 1);
			bundle->t_personal_eat_cnt_sem = make_sem_until_success(bundle->personal_eat_cnt_name[idx], 1);
			break ;
		}
		//printf("eat cnt sem : %s, eat time sem : %s\n", bundle->eat_cnt_sem_name, bundle->eat_time_sem_name);
		//rename_sem(bundle, idx + 1);
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
		if (WEXITSTATUS(status) == 1) //starve
		{
			kill(0, SIGINT);
			//여기서 죽이고나서 died 프린트하는게 나을 것 같은데? => 어차피 print_semaphore 있네
			break ;
		}
	}
}
