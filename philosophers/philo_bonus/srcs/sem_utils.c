/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:24:08 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/30 11:57:01 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	name_sems(t_bundle *bundle)
{
	bundle->sem_name = ft_strdup("sem");
	if (!bundle->sem_name)
		exit(11);
	bundle->print_sem_name = ft_strdup("print_sem");
	if (!bundle->print_sem_name)
		exit(12);
	bundle->eat_cnt_sem_name = ft_strdup("eat_cnt_sem");
	if (!bundle->eat_cnt_sem_name)
		exit(14);
}

sem_t	*make_sem_until_success(char *name, int s)
{
	sem_t	*ret;
	char	*temp;

	sem_unlink(name);
	ret = sem_open(name,
			O_CREAT | O_EXCL, 0660, s);
	while (ret == SEM_FAILED)
	{
		temp = name;
		name = ft_strjoin(name, "sem");
		free(temp);
		sem_unlink(name);
		ret = sem_open(name,
				O_CREAT | O_EXCL, 0660, s);
	}
	return (ret);
}

int	make_semaphores(t_bundle *bundle)
{
	int	idx;

	idx = -1;
	name_sems(bundle);
	malloc_2d_sem_names(bundle);
	while (++idx < bundle->num_of_philos)
	{
		bundle->eat_time_sem_name[idx] = name_eat_sems(idx, 0);
		bundle->personal_eat_cnt_name[idx] = name_eat_sems(idx, 1);
	}
	bundle->t_print_semaphore = \
	make_sem_until_success(bundle->print_sem_name, 1);
	bundle->t_semaphore = \
	make_sem_until_success(bundle->sem_name, bundle->num_of_philos);
	if (bundle->number_of_times_for_each != -2)
	{
		bundle->t_eat_cnt_sem = \
		make_sem_until_success(bundle->eat_cnt_sem_name, bundle->num_of_philos);
		while (++idx < bundle->num_of_philos)
			sem_wait(bundle->t_eat_cnt_sem);
	}
	return (0);
}

void	free_remains(t_bundle *bundle)
{
	int	idx;

	if (bundle->sem_name)
		free(bundle->sem_name);
	if (bundle->print_sem_name)
		free(bundle->print_sem_name);
	if (bundle->eat_cnt_sem_name)
		free(bundle->eat_cnt_sem_name);
	if (bundle->eat_time_sem_name)
	{
		idx = -1;
		while (++idx < bundle->num_of_philos)
			free(bundle->eat_time_sem_name[idx]);
		free(bundle->eat_time_sem_name);
	}
	if (bundle->personal_eat_cnt_name)
	{
		idx = -1;
		while (++idx < bundle->num_of_philos)
			free(bundle->personal_eat_cnt_name[idx]);
		free(bundle->personal_eat_cnt_name);
	}
}

void	delete_semaphores(t_bundle *bundle)
{
	int	idx;

	if (sem_close(bundle->t_semaphore) == -1)
		exit(5);
	if (sem_unlink(bundle->sem_name) == -1)
		exit(6);
	if (sem_close(bundle->t_print_semaphore) == -1)
		exit(7);
	if (sem_unlink(bundle->print_sem_name) == -1)
		exit(8);
	if (sem_close(bundle->t_eat_cnt_sem) == -1)
		exit(7);
	if (sem_unlink(bundle->eat_cnt_sem_name) == -1)
		exit(8);
	idx = -1;
	while (++idx < bundle->num_of_philos)
	{
		if (sem_unlink(bundle->eat_time_sem_name[idx]) == -1)
			exit(9);
		if (sem_unlink(bundle->personal_eat_cnt_name[idx]) == -1)
			exit(10);
	}
}
