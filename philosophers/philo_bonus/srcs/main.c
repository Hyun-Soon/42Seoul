/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:40 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/30 11:49:19 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	null_init(t_bundle *bundle)
{
	bundle->sem_name = NULL;
	bundle->print_sem_name = NULL;
	bundle->eat_time_sem_name = NULL;
	bundle->eat_cnt_sem_name = NULL;
	bundle->personal_eat_cnt_name = NULL;
}

void	init_bundle(t_bundle *bundle, int argc, char **argv)
{
	null_init(bundle);
	bundle->eat_cnt = 0;
	bundle->hold_forks = 0;
	bundle->num_of_philos = ft_atoi(argv[1]);
	bundle->time_to_die = ft_atoi(argv[2]);
	bundle->time_to_eat = ft_atoi(argv[3]);
	bundle->time_to_sleep = ft_atoi(argv[4]);
	bundle->number_of_times_for_each = -2;
	bundle->odd_flag = bundle->num_of_philos % 2;
	if (argc == 6)
		bundle->number_of_times_for_each = ft_atoi(argv[5]);
	if (bundle->num_of_philos == -1
		|| bundle->number_of_times_for_each == -1
		|| bundle->time_to_die == -1
		|| bundle->time_to_eat == -1
		|| bundle->time_to_sleep == -1)
	{
		write(2, "arg err.\n", 9);
		exit(21);
	}
}

//void	check()
//{
//	system("leaks philo_bonus");
//}

int	main(int argc, char **argv)
{
	t_bundle	bundle;
	int			idx;

	if (argc < 5)
	{
		printf("Not enough args.\n");
		return (1);
	}
	init_bundle(&bundle, argc, argv);
	make_semaphores(&bundle);
	make_philosophers(&bundle);
	idx = -1;
	if (bundle.number_of_times_for_each != -2)
		while (++idx < bundle.num_of_philos)
			sem_wait(bundle.t_eat_cnt_sem);
	wait_philosophers(&bundle);
	delete_semaphores(&bundle);
	free_remains(&bundle);
	return (0);
}
