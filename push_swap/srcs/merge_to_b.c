/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_to_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:11:22 by soon              #+#    #+#             */
/*   Updated: 2023/09/11 13:52:25 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_to_b(t_stacks *stks, int size, int type)
{
	int	div_size[3];

	if (size == 1 || is_sorted(stks->stk_a, size, -type))
	{
		while (size--)
			ft_push(stks, PB);
		return ;
	}
	if (size == 2)
	{
		ft_swap(stks, SA);
		while (size--)
			ft_push(stks, PB);
		return ;
	}
	div_size[0] = size / 3;
	div_size[1] = size / 3 + size % 3;
	div_size[2] = size / 3;
	merge_to_b(stks, div_size[2], type);
	move_chunk_to_b_bottom(stks, div_size[2]);
	merge_to_a(stks, div_size[0], type);
	move_chunk_to_a_bottom(stks, div_size[0]);
	merge_to_a(stks, div_size[1], -type);
	finally_merge_to_b(stks, div_size, type);
}

void	finally_merge_to_b(t_stacks *stks, int *size, int type)
{
	int			total_size;
	long long	values[3];

	total_size = size[0] + size[1] + size[2];
	while (total_size--)
	{
		values[0] = update_a_bottom_value(stks, size[0], type);
		values[1] = update_a_top_value(stks, size[1], type);
		values[2] = update_b_bottom_value(stks, size[2], type);
		chunks_to_b(stks, values, size, type);
	}
}

void	chunks_to_b(t_stacks *stks, long long *values, int *size, int type)
{
	if (type == ASCEND)
		chunks_to_b_ascend(stks, values, size);
	else
		chunks_to_b_descend(stks, values, size);
}

void	chunks_to_b_ascend(t_stacks *stks, long long *values, int *size)
{
	if (values[0] > values[1] && values[0] > values[2])
	{
		ft_rotate(stks, RRA);
		ft_push(stks, PB);
		size[0]--;
	}
	else if (values[1] > values[0] && values[1] > values[2])
	{
		ft_push(stks, PB);
		size[1]--;
	}
	else
	{
		if (stks->stk_b->value != values[2])
			ft_rotate(stks, RRB);
		size[2]--;
	}
}

void	chunks_to_b_descend(t_stacks *stks, long long *values, int *size)
{
	if (values[0] < values[1] && values[0] < values[2])
	{
		ft_rotate(stks, RRA);
		ft_push(stks, PB);
		size[0]--;
	}
	else if (values[1] < values[0] && values[1] < values[2])
	{
		ft_push(stks, PB);
		size[1]--;
	}
	else
	{
		if (stks->stk_b->value != values[2])
			ft_rotate(stks, RRB);
		size[2]--;
	}
}
