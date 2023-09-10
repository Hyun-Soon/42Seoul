/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soon <soon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:09:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/10 19:19:41 by soon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

int main(int argc, char **argv)
{
	int		inp_list_size;
	int		*inp_list;
	int			opt_flag;
	t_stacks	stks;

	inp_list_size = 0;
	parse_input(argc, argv, &inp_list_size, &inp_list);
	make_stacks(&stks, inp_list_size, inp_list);
	if (inp_list_size <= 1)
		exit(0);
	if (inp_list_size <= 5)
		hard_sort(inp_list, inp_list_size, &stks, stks.stk_a);
	if (is_sorted(stks.stk_a, inp_list_size, ASCEND))
		exit(0);
	merge_to_a(&stks, inp_list_size, ASCEND);
	opt_flag = 1;
	while (stks.cmd_list && opt_flag == 1)
		optimize_cmds(&stks, &opt_flag);
	print_result(&stks);
	clear_stacks(&stks, inp_list);
	return (0);
}

int	is_sorted(t_dll *stk, int size, int type)
{
	t_dll	*temp;

	if (!stk)
		return (0);
	temp = stk;
	if (type == ASCEND)
	{
		while (--size)
		{
			if (temp->value > temp->next->value)
				return (0);
			temp = temp->next;
		}
	}
	else if (type == DESCEND)
	{
		while (--size)
		{
			if (temp->value < temp->next->value)
				return (0);
			temp = temp->next;
		}
	}
	return (1);
}
