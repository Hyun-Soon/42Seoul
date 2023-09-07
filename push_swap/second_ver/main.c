/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:09:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/07 22:33:23 by hyuim            ###   ########.fr       */
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
	if (inp_list_size <= 1)
		exit(0);
	if (inp_list_size <= 5)
		hard_sort(inp_list, inp_list_size, &stks, stks.stk_a);
	if (is_sorted(stks.stk_a, inp_list_size, ASCEND))
		exit(0);
	//go(&stks, inp_list_size, ASCEND);
	merge_to_a(&stks, inp_list_size, ASCEND);
	
	print_result(&stks);
	exit(0);
}

// void	go(t_stacks *stks, int size, int type)
// {
// 	int	div_size[3];

// 	div_size[0] = size / 3;
// 	div_size[1] = size / 3 + size % 3;
// 	div_size[2] = size / 3;
// 	merge_to_b(stks, div_size[0], type); //3
// 	merge_to_b(stks, div_size[1], -type); //4
// 	merge_to_a(stks, div_size[2], type); //3
// 	finally_merge_to_a(stks, div_size, type);
// }

void	merge_to_a(t_stacks *stks, int size, int type)
{
	int	div_size[3];

	if (is_sorted(stks->stk_a, size, type)) ///
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
	//move_chunk_to_b_top(stks, div_size[1]);
	merge_to_a(stks, div_size[2], type);
	move_chunk_to_a_bottom(stks, div_size[2]);
	finally_merge_to_a(stks, div_size, type);
}

void	merge_to_b(t_stacks *stks, int size, int type)
{
	int	div_size[3];

	if (size == 1 || is_sorted(stks->stk_a, size, -type)) // -typeㅇ어야 하하나나?
	{
		while (size--)
			ft_push(stks, PB);
		return ; ////
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
	//move_chunk_to_a_top(stks, div_size[1]);
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
		{
			if (type == ASCEND)
				a_bottom_value = -2200000000;
			else
				a_bottom_value = 2200000000;
		}
		else
			a_bottom_value = stks->stk_a->prev->value;
		if (!size[1])
		{
			if (type == ASCEND)
				a_top_value = -2200000000;
			else
				a_top_value = 2200000000;
		}
		else
			a_top_value = stks->stk_a->value;
		if (!size[2])
		{
			if (type == ASCEND)
				b_bottom_value = -2200000000;
			else
				b_bottom_value = 2200000000;
		}
		else
			b_bottom_value = stks->stk_b->prev->value;
		
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
				if (stks->stk_b->value != b_bottom_value)
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
				if (stks->stk_b->value != b_bottom_value)
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
		{
			if (type == ASCEND)
				b_bottom_value = -2200000000;
			else
				b_bottom_value = 2200000000;
		}
		else
			b_bottom_value = stks->stk_b->prev->value;
		if (!size[1])
		{
			if (type == ASCEND)
				b_top_value = -2200000000;
			else
				b_top_value = 2200000000;
		}
		else
			b_top_value = stks->stk_b->value;
		if (!size[2])
		{
			if (type == ASCEND)
				a_bottom_value = -2200000000;
			else
				a_bottom_value = 2200000000;
		}
		else
			a_bottom_value = stks->stk_a->prev->value;
		
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
	// if (!stks->stk_a)
	// 	rotate = 0;
	if (rotate)
	{
		while (++idx < size)
			ft_rotate(stks, RA);
	}
}

// void	move_chunk_to_a_top(t_stacks *stks, int size)
// {
// 	while (stks->stk_b && size--)
// 		ft_push(stks, PA);
// }

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
	// if (!stks->stk_b)
	// 	rotate = 0;
	// while (stks->stk_a && ++idx < size)
	// 	ft_push(stks, PB);// finally b merge 했으면 이게 필요가 없지!!!!!!!!!
	if (rotate)
	{
		while (++idx < size)
			ft_rotate(stks, RB);
	}
}

// void	move_chunk_to_b_top(t_stacks *stks, int size) // finally b merge 했으면 넌 아예 필요가 없다
// {
// 	while (stks->stk_a && size--)
// 		ft_push(stks, PB);
// }

int	is_sorted(t_dll *stk, int size, int type)
{
	t_dll	*temp;

	if (!stk)
		return (0); // 왜 이 케이스가 생기지?
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
