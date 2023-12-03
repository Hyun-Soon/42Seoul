/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:20:53 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/03 13:10:42 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

char	*ft_chardup(int c)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * 2);
	if (!ret)
		exit(255);
	ret[0] = c;
	ret[1] = 0;
	return (ret);
}

char	*name_eat_sems(int idx, int noise)
{
	int		hundred;
	int		ten;
	int		one;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * 5);
	if (!ret)
		exit(35);
	ret[3] = 's' + noise;
	ret[4] = '\0';
	hundred = idx / 100;
	ten = idx / 10;
	one = idx % 10;
	ret[0] = hundred + '0';
	ret[1] = ten + '0';
	ret[2] = one + '0';
	return (ret);
}

void	malloc_2d_sem_names(t_bundle *bundle)
{
	bundle->eat_time_sem_name = \
	(char **)malloc(sizeof(char *) * (bundle->num_of_philos + 1));
	if (!bundle->eat_time_sem_name)
		exit(33);
	bundle->personal_eat_cnt_name = \
	(char **)malloc(sizeof(char *) * (bundle->num_of_philos + 1));
	if (!bundle->personal_eat_cnt_name)
		exit(34);
	bundle->eat_time_sem_name[bundle->num_of_philos] = NULL;
	bundle->personal_eat_cnt_name[bundle->num_of_philos] = NULL;
}

void	print_eating(t_bundle *bundle, struct timeval s_now)
{
	sem_wait(bundle->t_print_semaphore);
	printf("%ld	%d is eating\n",
		get_timestamp(bundle, s_now), bundle->id + 1);
	sem_post(bundle->t_print_semaphore);
}
