/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:24:08 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/28 15:11:14 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	malloc_sem(t_bundle *bundle)
{
	bundle->sem_name = (char **)malloc(sizeof(char *) * 2);
	if (!bundle->sem_name)
		exit(11);
	bundle->s_semaphore = (sem_t **)malloc(sizeof(sem_t *) * 2);
	if (!bundle->s_semaphore)
		exit(12);
	bundle->sem_name[0] = ft_strdup("a");
	if (!bundle->sem_name[0])
		exit(13);
	bundle->sem_name[1] = ft_strdup("b");
	if (!bundle->sem_name[1])
		exit(14);
}

void	pre_unlink_sem(t_bundle *bundle)
{
	malloc_sem(bundle);
	sem_unlink(bundle->sem_name[0]);
	sem_unlink(bundle->sem_name[1]);
	sem_unlink("print_sem");
}

int	make_semaphore(t_bundle *bundle)
{
	char	*temp;
	int		idx;
	int		num_of_forks;

	pre_unlink_sem(bundle);
	bundle->s_print_semaphore = \
		sem_open("print_sem", O_CREAT | O_EXCL, 0660, 1);
	idx = -1;
	num_of_forks = bundle->num_of_philos / 2 + 1;
	while (++idx < 2)
	{
		bundle->s_semaphore[idx] = \
		sem_open(bundle->sem_name[idx], O_CREAT | O_EXCL, 0660, num_of_forks);
		while (bundle->s_semaphore[idx] == SEM_FAILED)
		{
			temp = bundle->sem_name[idx];
			bundle->sem_name[idx] = ft_strjoin(bundle->sem_name[idx], "sem");
			free(temp);
			sem_unlink(bundle->sem_name[idx]);
			bundle->s_semaphore[idx] = sem_open(bundle->sem_name[idx],
					O_CREAT | O_EXCL, 0660, num_of_forks);
		}
		num_of_forks = bundle->num_of_philos / 2;
	}
	return (0);
}

void	free_remains(t_bundle *bundle)
{
	if (bundle->sem_name)
	{
		free(bundle->sem_name[0]);
		free(bundle->sem_name[1]);
		free(bundle->sem_name);
	}
}

void	delete_semaphores(t_bundle *bundle)
{
	if (sem_close(bundle->s_semaphore[0]) == -1)
		exit(5);
	if (sem_close(bundle->s_semaphore[1]) == -1)
		exit(6);
	if (sem_unlink(bundle->sem_name[0]) == -1)
		exit(7);
	if (sem_unlink(bundle->sem_name[1]) == -1)
		exit(8);
	if (sem_close(bundle->s_print_semaphore) == -1)
		exit(9);
}
