/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:58:24 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/04 20:59:31 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	make_stacks(t_stacks *stacks, int inp_num, int *inp_list)
{
	stacks->stk_a = make_stack_a(inp_list, inp_num);
	stacks->stk_b = NULL;
	stacks->chunk_stk_a = make_chunk_stack_a(inp_num, inp_list, stacks);
	stacks->chunk_stk_b = NULL;
	stacks->cmd_list = NULL;

////////////////////***************TEST*********************////////////////////////
	// t_dll *temp = stacks->stk_a;
	// t_dll *temp2 = stacks->chunk_stk_a;
	// while (stacks->stk_a->next != temp)
	// {
	// 	printf("stack a : %d\n", stacks->stk_a->value);
	// 	stacks->stk_a = stacks->stk_a->next;
	// }
	// printf("stack a : %d\n\n", stacks->stk_a->value);
	// while (stacks->chunk_stk_a->next != temp2)
	// {
	// 	printf("chunk stack a - type, size : %d, %d\n", stacks->chunk_stk_a->type, stacks->chunk_stk_a->chunk_size);
	// 	stacks->chunk_stk_a = stacks->chunk_stk_a->next;
	// }
	// printf("chunk stack a - type, size : %d, %d\n\n", stacks->chunk_stk_a->type, stacks->chunk_stk_a->chunk_size);
	
	// printf("%d\n", stacks->initial_chunk_stk_size);
/////////////////////****************************************/////////////////////

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