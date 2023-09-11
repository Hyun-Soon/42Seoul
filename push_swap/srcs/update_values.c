/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soon <soon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:14:25 by soon              #+#    #+#             */
/*   Updated: 2023/09/10 19:15:29 by soon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long long	out_of_comparison(int type)
{
	if (type == ASCEND)
		return (-2200000000);
	else
		return (2200000000);
}

long long	update_a_top_value(t_stacks *stks, int chunk_size, int type)
{
	if (!chunk_size)
		return (out_of_comparison(type));
	else
		return (stks->stk_a->value);
}

long long	update_a_bottom_value(t_stacks *stks, int chunk_size, int type)
{
	if (!chunk_size)
		return (out_of_comparison(type));
	else
		return (stks->stk_a->prev->value);
}

long long	update_b_bottom_value(t_stacks *stks, int chunk_size, int type)
{
	if (!chunk_size)
		return (out_of_comparison(type));
	else
		return (stks->stk_b->prev->value);
}

long long	update_b_top_value(t_stacks *stks, int chunk_size, int type)
{
	if (!chunk_size)
		return (out_of_comparison(type));
	else
		return (stks->stk_b->value);
}
