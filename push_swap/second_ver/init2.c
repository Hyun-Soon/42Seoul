/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:58:24 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/07 17:12:19 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	make_stacks(t_stacks *stacks, int inp_num, int *inp_list)
{
	stacks->stk_a = make_stack_a(inp_list, inp_num);
	stacks->stk_b = NULL;
	stacks->cmd_list = NULL;
}

int	get_triangle_nums(int total_size)
{
	int	n;

	if (total_size <= 3)
		return (total_size);
	n = 3;
	while (total_size > n)
		n *= 9;
	return (n / 9);
}

int	check_des_asc(int *idx, int inp_num, int *inp_list, int *chunk_size)
{
	if ((*idx) + 1 > inp_num)
		return (0);
	if ((*idx) + 1 == inp_num)
	{
		*chunk_size = 1;
		(*idx)++;
		return (1);
	}
	*chunk_size = 0;
	while (++(*idx) < inp_num)
	{
		if (inp_list[*idx - 1] < inp_list[*idx] && *chunk_size >= 0)
			(*chunk_size)++;
		else if (inp_list[*idx - 1] > inp_list[*idx] && *chunk_size <= 0)
			(*chunk_size)--;
		else
			break;
	}
	if (*chunk_size >= 0)
		(*chunk_size)++;
	else
		(*chunk_size)--;
	return (1);
}