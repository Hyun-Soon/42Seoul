/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:09:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/06 22:24:29 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"
#include <stdio.h> /////////////////////////////////

void	check(void)
{
	system("leaks --quiet a.out");
}

int main(int argc, char **argv)
{
	int		*inp_list;
	int		inp_list_size;
	t_stacks	stks;

	inp_list_size = 0;
	inp_list = parse_input(argc, argv, &inp_list_size);
	make_stacks(&stks, inp_list_size, inp_list);
	if (inp_list_size <= 1 || (stks.initial_chunk_stk_size == 1 && stks.chunk_stk_a->type == ASCEND))
		exit(0);
	if (inp_list_size <= 5)
		hard_sort(inp_list, inp_list_size, &stks, stks.stk_a);

	merge_to_a(&stks, inp_list_size, ASCEND);

	print_stcks(stks);
	print_chunk_stcks(stks);
	exit(0);
}

void	merge_to_a(t_stacks *stks, int size, int type)
{
	int	div_size[3];

	if (size == 1 || is_sorted(stks->stk_a, size, type)) ///
		return ;
	if (size == 2)
	{
		ft_swap(stks, SA);
		return ;
	}
	div_size[0] = size / 3;
	div_size[1] = size / 3 + size % 3;
	div_size[2] = size / 3;

	merge_to_b(stks, div_size[0], -type);
	move_chunk_to_b_bottom(stks, div_size[0]);
	merge_to_b(stks, div_size[1], type);
	move_chunk_to_b_top(stks, div_size[1]);
	merge_to_a(stks, div_size[2], type);
	move_chunk_to_a_bottom(stks, div_size[2]);
	finally_merge_to_a(stks, div_size, type);
}

void	merge_to_b(t_stacks *stks, int size, int type)
{
	int	div_size[3];

	if (size == 1 || is_sorted(stks->stk_a, size, type))
		return ;
	if (size == 2)
	{
		ft_swap(stks, SA);
		return ;
	}
	div_size[0] = size / 3;
	div_size[1] = size / 3 + size % 3;
	div_size[2] = size / 3;

	merge_to_a(stks, div_size[0], -type);
	move_chunk_to_a_bottom(stks, div_size[0]);
	merge_to_a(stks, div_size[1], type);
	move_chunk_to_a_top(stks, div_size[1]);
	merge_to_b(stks, div_size[2], type);
	move_chunk_to_b_bottom(stks, div_size[2]);
	finally_merge_to_b(stks, div_size, type);
}

void	finally_merge_to_b(t_stacks *stks, int *size, int type)
{
	//[0]a_bottom, [1]a_top, [2]b_bottom
	int			total_size;
	long long	a_bottom_value;
	long long	a_top_value;
	long long	b_bottom_value;

	total_size = size[0] + size[1] + size[2];
	while (total_size--)
	{
		if (!size[0])
			a_bottom_value = -2200000000;
		else
			a_bottom_value = stks->stk_a->prev->value;
		if (!size[1])
			a_top_value = -2200000000;
		else
			a_top_value = stks->stk_a->value;
		if (!size[2])
			b_bottom_value = -2200000000;
		else
			b_bottom_value = stks->stk_b->value;
		
		if (type == ASCEND)
		{
			if (a_bottom_value > a_top_value && a_bottom_value > b_bottom_value)
			{
				ft_rotate(stks, RRA);
				ft_push(stks, PB);
				size[0]--;
			}
			else if (a_top_value > a_bottom_value && a_top_value > b_bottom_value)
			{
				ft_push(stks, PB);
				size[1]--;
			}
			else
			{
				ft_rotate(stks, RRB);
				size[2]--;
			}
		}
		else
		{
			if (a_bottom_value < a_top_value && a_bottom_value < b_bottom_value)
			{
				ft_rotate(stks, RRA);
				ft_push(stks, PB);
				size[0]--;
			}
			else if (a_top_value < a_bottom_value && a_top_value < b_bottom_value)
			{
				ft_push(stks, PB);
				size[1]--;
			}
			else
			{
				ft_rotate(stks, RRB);
				size[2]--;
			}
		}
	}
}

void	finally_merge_to_a(t_stacks *stks, int *size, int type)
{
	//[0]b_bottom, [1]b_top, [2]a_bottom
	int			total_size;
	long long	b_bottom_value;
	long long	b_top_value;
	long long	a_bottom_value;

	total_size = size[0] + size[1] + size[2];
	while (total_size--)
	{
		if (!size[0])
			b_bottom_value = -2200000000;
		else
			b_bottom_value = stks->stk_b->prev->value;
		if (!size[1])
			b_top_value = -2200000000;
		else
			b_top_value = stks->stk_b->value;
		if (!size[2])
			a_bottom_value = -2200000000;
		else
			a_bottom_value = stks->stk_a->value;
		
		if (type == ASCEND)
		{
			if (b_bottom_value > b_top_value && b_bottom_value > a_bottom_value)
			{
				ft_rotate(stks, RRB);
				ft_push(stks, PA);
				size[0]--;
			}
			else if (b_top_value > b_bottom_value && b_top_value > a_bottom_value)
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
		else
		{
			if (b_bottom_value < b_top_value && b_bottom_value < a_bottom_value)
			{
				ft_rotate(stks, RRB);
				ft_push(stks, PA);
				size[0]--;
			}
			else if (b_top_value < b_bottom_value && b_top_value < a_bottom_value)
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
	}
}

void	move_chunk_to_a_bottom(t_stacks *stks, int size)
{
	int	rotate;
	int	idx;

	rotate = 1;
	idx = -1;
	if (!stks->stk_a)
		rotate = 0;
	while (++idx < size)
		ft_push(stks, PA);
	if (rotate)
	{
		idx = -1;
		while (++idx < size)
			ft_rotate(stks, RA);
	}
}

void	move_chunk_to_a_top(t_stacks *stks, int size)
{
	while (size--)
		ft_push(stks, PA);
}

void	move_chunk_to_b_bottom(t_stacks *stks, int size)
{
	int	rotate;
	int	idx;

	rotate = 1;
	idx = -1;
	if (!stks->stk_b)
		rotate = 0;
	while (++idx < size)
		ft_push(stks, PB);
	if (rotate)
	{
		idx = -1;
		while (++idx < size)
			ft_rotate(stks, RB);
	}
}

void	move_chunk_to_b_top(t_stacks *stks, int size)
{
	while (size--)
		ft_push(stks, PB);
}

int	is_sorted(t_dll *stk, int size, int type)
{
	t_dll	*temp;

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


int	get_stack_size(t_dll *stk)
{
	int		size;
	t_dll	*temp;

	if (stk == NULL)
		return (-1);
	size = 0;
	temp = stk;
	while (temp->next != stk)
		size++;
	size++;
	return (size);
}


void	print_chunk_stcks(t_stacks stks)
{
	t_chunk_dll	*temp_a;
	t_chunk_dll	*temp_b;
	temp_b = stks.chunk_stk_b;
	temp_a = stks.chunk_stk_a;
		printf("---------------print_chunk_stcks-----------\n\n");

	while (temp_a && temp_a->next != stks.chunk_stk_a)
	{
		printf("chunk a size : %d, type : %d\n", temp_a->chunk_size, temp_a->type);
		temp_a = temp_a->next;
	}
	if (temp_a)
		printf("last chunk a size : %d, type : %d\n", temp_a->chunk_size, temp_a->type);

	while (temp_b && temp_b->next != stks.chunk_stk_b)
	{
		printf("chunk b size : %d, type : %d\n", temp_b->chunk_size, temp_b->type);
		temp_b = temp_b->next;
	}
	if (temp_b)
		printf("last chunk b size : %d, type : %d\n", temp_b->chunk_size, temp_b->type);

	printf("-------------------------------------------\n\n");

}

void	print_stcks(t_stacks stks)
{
	t_dll	*temp_a;
	t_dll	*temp_b;
	t_list	*temp_cmd;
	temp_b = stks.stk_b;
	temp_a = stks.stk_a;
	temp_cmd = stks.cmd_list;

	printf("-----------------print_stcks--------------\n\n");
	printf("-----a-----\n");
	while (temp_a && temp_a->next != stks.stk_a)
	{
		printf("a: %d\n", temp_a->value);
		temp_a = temp_a->next;
	}
	if (temp_a)
		printf("a last : %d\n", temp_a->value);
	printf("-----------\n\n");

	printf("-----b-----\n");
	while (temp_b && temp_b->next != stks.stk_b)
	{
		printf("b: %d\n", temp_b->value);
		temp_b = temp_b->next;
	}
	if (temp_b)
		printf("b last: %d\n", temp_b->value);
	printf("-----------\n");

	while (temp_cmd && temp_cmd->content)
	{
		printf("cmd : %d\n", temp_cmd->content);
		temp_cmd = temp_cmd->next;
	}
	printf("------------------------------------------\n\n");

}
