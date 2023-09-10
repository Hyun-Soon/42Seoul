/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:09:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/08 16:20:46 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

void	check()
{
	system("leaks --quiet a.out");
}

int main(int argc, char **argv)
{
	int		inp_list_size;
	int		*inp_list;
	int			opt_flag;
	t_stacks	stks;

	// atexit(check);
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

void	ft_stackclear(t_dll *stk)
{
	t_dll	*temp;

	while (stk)
	{
		temp = stk->next;
		free(stk);
		stk = temp;
	}
	return ;
}

void	clear_stacks(t_stacks *stks, int *inp_list)
{
	free(inp_list);
	if (stks->stk_a)
		ft_stackclear(stks->stk_a);
	if (stks->stk_b)
		ft_stackclear(stks->stk_b);
	if (stks->cmd_list)
		ft_lstclear(stks->cmd_list);
}

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
long long	update_a_top_value(t_stacks *stks, int chunk_size, int type)
{
	if (!chunk_size)
		return (out_of_comparison(type));
	else
		return (stks->stk_a->value);
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

void	finally_merge_to_b(t_stacks *stks, int *size, int type)
{
	//[0]a_bottom [1]a_top [2]b_bottom
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

long long	out_of_comparison(int type)
{
	if (type == ASCEND)
		return (-2200000000);
	else
		return (2200000000);
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

long long	update_a_bottom_value(t_stacks *stks, int chunk_size, int type)
{
	if (!chunk_size)
		return (out_of_comparison(type));
	else
		return (stks->stk_a->prev->value);
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

void	chunks_to_a(t_stacks *stks, long long *values, int *size, int type)
{
	if (type == ASCEND)
		chunks_to_a_ascend(stks, values, size);
	else
		chunks_to_a_descend(stks, values, size);
}


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

void	print_result(t_stacks *stks)
{
	t_list *temp;

	temp = stks->cmd_list;
	while (temp && temp->content)
	{
		print_content(temp);
		temp = temp->next;
	}
}

void	print_content(t_list *temp)
{
	if (temp->content == SA)
		ft_printf("sa\n");
	else if (temp->content == SB)
		ft_printf("sb\n");
	else if (temp->content == SS)
		ft_printf("ss\n");
	else if (temp->content == PA)
		ft_printf("pa\n");
	else if (temp->content == PB)
		ft_printf("pb\n");
	else if (temp->content == RA)
		ft_printf("ra\n");
	else if (temp->content == RB)
		ft_printf("rb\n");
	else if (temp->content == RR)
		ft_printf("rr\n");
	else if (temp->content == RRA)
		ft_printf("rra\n");
	else if (temp->content == RRB)
		ft_printf("rrb\n");
	else if (temp->content == RRR)
		ft_printf("rrr\n");
}
void	optimize_cmds(t_stacks *stks, int *flag)
{
	t_list	*temp;
	int		cmds_sum;
	
	temp = stks->cmd_list;
	*flag = 0;
	while (temp->next)
	{
		cmds_sum = temp->content + temp->next->content;
		if (cmds_sum == 0)
		{
			ft_lstdelone(temp->next);
			ft_lstdelone(temp);
			*flag = 1;
			return ;
		}
		else if (cmds_sum == SS || cmds_sum == RR || cmds_sum == RRR)
		{
			merge_cmd(temp, cmds_sum, flag);
			return ;
		}
		temp = temp->next;
	}
}

void	merge_cmd(t_list *cmd_node, int cmd, int *flag)
{
	t_list	*new_cmd;
	t_list	*temp_prev;
	t_list	*temp_next;

	temp_prev = cmd_node->prev;
	temp_next = cmd_node->next->next;
	ft_lstdelone(cmd_node->next);
	ft_lstdelone(cmd_node);
	new_cmd = ft_lstnew(cmd);
	temp_prev->next = new_cmd;
	new_cmd->prev = temp_prev;
	new_cmd->next = temp_next;
	temp_next->prev = new_cmd;
	*flag = 1;
}
