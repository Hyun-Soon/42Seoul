/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_to_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soon <soon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:08:08 by soon              #+#    #+#             */
/*   Updated: 2023/09/10 19:10:10 by soon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	merge_to_a(t_stacks *stks, int size, int type)
{
	int	div_size[3];

	if (is_sorted(stks->stk_a, size, type))
		return ;
	if (size == 2)
	{
		ft_swap(stks, SA);
		return ;
	}
	div_size[0] = size / 3;
	div_size[1] = size / 3 + size % 3;
	div_size[2] = size / 3;

	merge_to_b(stks, div_size[0], type);
	move_chunk_to_b_bottom(stks, div_size[0]);
	merge_to_b(stks, div_size[1], -type);
	merge_to_a(stks, div_size[2], type);
	move_chunk_to_a_bottom(stks, div_size[2]);
	finally_merge_to_a(stks, div_size, type);
}

void	finally_merge_to_a(t_stacks *stks, int *size, int type)
{
	//[0]b_bottom, [1]b_top, [2]a_bottom
	int			total_size;
	long long	values[3];

	total_size = size[0] + size[1] + size[2];
	while (total_size--)
	{
		values[0] = update_b_bottom_value(stks, size[0], type);
		values[1] = update_b_top_value(stks, size[1], type);
		values[2] = update_a_bottom_value(stks, size[2], type);
		chunks_to_a(stks, values, size, type);
	}
}

void	chunks_to_a(t_stacks *stks, long long *values, int *size, int type)
{
	if (type == ASCEND)
		chunks_to_a_ascend(stks, values, size);
	else
		chunks_to_a_descend(stks, values, size);
}

void	chunks_to_a_ascend(t_stacks *stks, long long *values, int *size)
{
	if (values[0] > values[1] && values[0] > values[2])
	{
		ft_rotate(stks, RRB);
		ft_push(stks, PA);
		size[0]--;
	}
	else if (values[1] > values[0] && values[1] > values[2])
	{
		ft_push(stks, PA);
		size[1]--;
	}
	else
	{
		ft_rotate(stks, RRA);
		size[2]--;
	}
}

void	chunks_to_a_descend(t_stacks *stks, long long *values, int *size)
{
	if (values[0] < values[1] && values[0] < values[2])
	{
		ft_rotate(stks, RRB);
		ft_push(stks, PA);
		size[0]--;
	}
	else if (values[1] < values[0] && values[1] < values[2])
	{
		ft_push(stks, PA);
		size[1]--;
	}
	else
	{
		ft_rotate(stks, RRA);
		size[2]--;
	}
}