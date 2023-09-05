/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:48:30 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/04 20:17:12 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void ft_swap(t_stacks *stacks, int cmd)
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

void	ft_chunk_swap(t_stacks *stacks, int cmd)
{
	int	temp;

	if (cmd == CSA)
	{
		temp = stacks->chunk_stk_a->chunk_size;
		stacks->chunk_stk_a->chunk_size = stacks->chunk_stk_a->next->chunk_size;
		stacks->chunk_stk_a->next->chunk_size = temp;
		temp = stacks->chunk_stk_a->type;
		stacks->chunk_stk_a->type = stacks->chunk_stk_a->next->type;
		stacks->chunk_stk_a->next->type = temp;
	}
	else if (cmd == CSB)
	{
		temp = stacks->chunk_stk_b->chunk_size;
		stacks->chunk_stk_b->chunk_size = stacks->chunk_stk_b->next->chunk_size;
		stacks->chunk_stk_b->next->chunk_size = temp;
		temp = stacks->chunk_stk_b->type;
		stacks->chunk_stk_b->type = stacks->chunk_stk_b->next->type;
		stacks->chunk_stk_b->next->type = temp;
	}
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

void	ft_chunk_push(t_stacks *stacks, int cmd, int reverse_flag)
{
	t_chunk_dll	*temp;

	if (cmd == CPA)
	{
		temp = cpop(&(stacks->chunk_stk_b));
		if (reverse_flag)
			temp->type *= -1;
		cpush(temp, &(stacks->chunk_stk_a));
	}
	else if (cmd == CPB)
	{
		temp = cpop(&(stacks->chunk_stk_a));
		if (reverse_flag)
			temp->type *= -1;
		cpush(temp, &(stacks->chunk_stk_b));
	}
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

void	ft_chunk_rotate(t_stacks *stacks, int cmd)
{
	if (cmd == CRA)
		stacks->chunk_stk_a = stacks->chunk_stk_a->next;
	else if (cmd == CRB)
		stacks->chunk_stk_b = stacks->chunk_stk_b->next;
	else if (cmd == CRRA)
		stacks->chunk_stk_a = stacks->chunk_stk_a->prev;
	else if (cmd == CRRB)
		stacks->chunk_stk_b = stacks->chunk_stk_b->prev;
}