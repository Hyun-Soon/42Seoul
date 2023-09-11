/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:14:57 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/11 17:17:38 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"
#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	int			inp_list_size;
	int			*inp_list;
	t_stacks	stks;
	char		*inp_cmd;

	inp_list_size = 0;
	parse_input(argc, argv, &inp_list_size, &inp_list);
	make_stacks(&stks, inp_list_size, inp_list);
	while (1)
	{
		inp_cmd = get_next_line(0);
		if (!inp_cmd)
		{
			print_sort_result(&stks, inp_list_size);
			break ;
		}
		exec_cmd(&stks, inp_cmd);
		free(inp_cmd);
		inp_cmd = NULL;
	}
	clear_stacks(&stks, inp_list);
	return (0);
}

void	print_sort_result(t_stacks *stks, int inp_list_size)
{
	if (!(stks->stk_b) && is_sorted(stks->stk_a, inp_list_size, ASCEND))
		ft_printf("%s\n", "OK");
	else
		ft_printf("%s\n", "KO");
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
