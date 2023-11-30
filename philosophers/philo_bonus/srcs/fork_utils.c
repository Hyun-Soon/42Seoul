/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:30:01 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/30 11:30:33 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	up_hold_forks(t_bundle *bundle)
{
	sem_wait(bundle->t_personal_eat_cnt_sem);
	bundle->hold_forks++;
	sem_post(bundle->t_personal_eat_cnt_sem);
}

void	down_hold_forks(t_bundle *bundle)
{
	sem_wait(bundle->t_personal_eat_cnt_sem);
	bundle->hold_forks--;
	sem_post(bundle->t_personal_eat_cnt_sem);
}
