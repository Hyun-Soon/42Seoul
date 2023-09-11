/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stk_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:59:58 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/11 13:51:00 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_dll	*pop(t_dll **stk)
{
	t_dll	*temp;

	if (!*stk)
		return (NULL);
	if ((*stk)->next == *stk && (*stk)->prev == *stk)
	{
		temp = *stk;
		*stk = NULL;
		return (temp);
	}
	temp = *stk;
	*stk = (*stk)->next;
	(*stk)->prev = (*stk)->prev->prev;
	(*stk)->prev->next = (*stk);
	temp->next = temp;
	temp->prev = temp;
	return (temp);
}

void	push(t_dll *node, t_dll **stk)
{
	if (!*stk)
	{
		*stk = node;
		return ;
	}
	node->next = *stk;
	node->prev = (*stk)->prev;
	(*stk)->prev->next = node;
	(*stk)->prev = node;
	*stk = node;
}
