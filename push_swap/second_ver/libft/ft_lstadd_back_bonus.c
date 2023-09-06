/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:09:01 by hyuim             #+#    #+#             */
/*   Updated: 2023/08/16 19:14:35 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


void	ft_lstadd_back(t_stacks *stks, t_list *new)
{
	t_list	*temp;

	if (!(stks->cmd_list))
	{
		stks->cmd_list = new;
		return ;
	}
	temp = stks->cmd_list;
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
	new->prev = temp;
	return ;
}
