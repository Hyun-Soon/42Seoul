/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:48:30 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/11 13:26:01 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(t_stacks *stacks, int cmd)
{
	int	temp;

	if (cmd == SA)
	{
		temp = stacks->stk_a->value;
		stacks->stk_a->value = stacks->stk_a->next->value;
		stacks->stk_a->next->value = temp;
	}
	else if (cmd == SB)
	{
		temp = stacks->stk_b->value;
		stacks->stk_b->value = stacks->stk_b->next->value;
		stacks->stk_b->next->value = temp;
	}
	ft_lstadd_back(stacks, ft_lstnew(cmd));
}

void	ft_push(t_stacks *stacks, int cmd)
{
	t_dll	*temp;

	if (cmd == PA)
	{
		temp = pop(&(stacks->stk_b));
		push(temp, &(stacks->stk_a));
	}
	else if (cmd == PB)
	{
		temp = pop(&(stacks->stk_a));
		push(temp, &(stacks->stk_b));
	}
	ft_lstadd_back(stacks, ft_lstnew(cmd));
}

void	ft_rotate(t_stacks *stacks, int cmd)
{
	if (cmd == RA)
		stacks->stk_a = stacks->stk_a->next;
	else if (cmd == RB)
		stacks->stk_b = stacks->stk_b->next;
	else if (cmd == RRA)
		stacks->stk_a = stacks->stk_a->prev;
	else if (cmd == RRB)
		stacks->stk_b = stacks->stk_b->prev;
	ft_lstadd_back(stacks, ft_lstnew(cmd));
}
