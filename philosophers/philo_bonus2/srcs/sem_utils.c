/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:24:08 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/28 23:30:22 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	pre_unlink_sem(t_bundle *bundle)
{
	bundle->sem_name = ft_strdup("sem");
	if (!bundle->sem_name)
		exit(11);
	bundle->print_sem_name = ft_strdup("print_sem");
	if (!bundle->print_sem_name)
		exit(12);
	sem_unlink(bundle->sem_name);
	sem_unlink(bundle->print_sem_name);
}

sem_t	*make_sem_until_success(char *name, int s)
{
	sem_t	*ret;
	char	*temp;

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
	pre_unlink_sem(bundle);
	bundle->s_print_semaphore = make_sem_until_success(bundle->print_sem_name, 1);
	bundle->s_semaphore = make_sem_until_success(bundle->sem_name, bundle->num_of_philos);
	return (0);
}

void	free_remains(t_bundle *bundle)
{
	if (bundle->sem_name)
		free(bundle->sem_name);
	if (bundle->print_sem_name)
		free(bundle->print_sem_name);
}

void	delete_semaphores(t_bundle *bundle)
{
	if (sem_close(bundle->s_semaphore) == -1)
		exit(5);
	if (sem_unlink(bundle->sem_name) == -1)
		exit(6);
	if (sem_close(bundle->s_print_semaphore) == -1)
		exit(7);
	if (sem_unlink(bundle->print_sem_name) == -1)
		exit(8);
}
