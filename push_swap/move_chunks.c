/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soon <soon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:16:10 by soon              #+#    #+#             */
/*   Updated: 2023/09/10 19:18:37 by soon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_chunk_to_a_bottom(t_stacks *stks, int size)
{
	t_dll	*temp;
	int	rotate;
	int	idx;

	rotate = 0;
	idx = -1;
	if (stks->stk_a)
	{
		temp = stks->stk_a;
		while (++idx < size - 1)
			temp = temp->next;
		if (temp->next != stks->stk_a)
			rotate = 1;
		idx = -1;
	}
	if (rotate)
	{
		while (++idx < size)
			ft_rotate(stks, RA);
	}
}

void	move_chunk_to_b_bottom(t_stacks *stks, int size)
{
	t_dll	*temp;
	int	rotate;
	int	idx;

	rotate = 0;
	idx = -1;
	if (stks->stk_b)
	{
		temp = stks->stk_b;
		while (++idx < size - 1)
			temp = temp->next;
		if (temp->next != stks->stk_b)
			rotate = 1;
		idx = -1;
	}
	if (rotate)
	{
		while (++idx < size)
			ft_rotate(stks, RB);
	}
}
