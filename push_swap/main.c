/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:09:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/05 18:08:32 by hyuim            ###   ########.fr       */
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
	int		sorted_order[2188];
	int		first_b_num;
	t_stacks	stks;

	inp_list_size = 0;
	inp_list = parse_input(argc, argv, &inp_list_size);
	make_stacks(&stks, inp_list_size, inp_list);
	if (inp_list_size <= 1 || (stks.initial_chunk_stk_size == 1 && stks.chunk_stk_a->type == ASCEND))
		exit(0);
	if (inp_list_size <= 5)
		hard_sort(inp_list, inp_list_size, &stks, stks.stk_a);

	//*****************b에  정렬할  모양  알아내기*************************
	int	exp = 0;
	int	offset = ft_pow(3, exp);
	first_b_num = get_triangle_nums(stks.initial_chunk_stk_size);
	sorted_order[0] = 1014; /////////////
	sorted_order[1] = 1;
	while (offset < first_b_num)
	{
		int	idx = -1;
		while (offset - ++idx >= 1)
		{
			sorted_order[1 + offset + idx] = -sorted_order[offset - idx];
			sorted_order[1 + 2 * offset + idx] = -sorted_order[offset - idx];
		}
		exp++;
		offset = ft_pow(3, exp);
	}

	//****************sorted order에 맞춰서 b로 옮기기****************************
	// printf("[");
	// for (int i = 1 ; i<=first_b_num; i++)
	// 	printf("%d, ", sorted_order[i]);
	// printf("]\n");
	first_move_to_b(&stks, first_b_num, sorted_order);

	if (stks.stk_a)
		insert_remainder(&stks);
	print_stcks(stks);
	print_chunk_stcks(stks);
	exit(0);
}

void	insert_remainder(t_stacks *stks)
{
	int	total;
	int	now;
	t_chunk_dll *temp;

	total = count_remainder(stks);
	now = 0;
	//TODO :: insert efficiently
	while (total--)
	{
		insert_to_b(stks, &now);
	}
}

void	insert_to_b(t_stacks *stks, int *now)
{
	int	pos;
	int	move_after_push;

	move_after_push = 0;
	pos = find_pos(stks->stk_a->value, stks);
	if (pos == -1)
		printf("wtf\n");
	//pos가 위로 가는게 더 빠를 수도 있음. 확인하자.
	*now += pos;
	optimize_now();
}


int	find_pos(int value, t_stacks *stks)
{
	int	b_stk_size;
	int	idx;
	t_dll	*temp;

	b_stk_size = get_stack_size(stks->stk_b);
	temp = stks->stk_b;
	idx = -1;
	while (++idx < b_stk_size)
	{
		if ((temp->prev->value < value && value < temp->value) 
			|| (temp->prev->value > value && value > temp->value))
			if (is_chunk_or_edge(idx, stks) == 1)
				return (idx);
	}
	if (idx == b_stk_size)
		return (-1);
	return (-1); // 밖에 함수에선 idx 자리에 노드만 추가하고, chunk_size, 
}

int	check_possible_edge(t_chunk_dll *chunk_node, t_stacks *stks)
{

	if ((chunk_node->type == ASCEND && chunk_node->prev->type == DESCEND) || (chunk_node->type == DESCEND && chunk_node->prev->type == ASCEND))
	{
		chunk_node->chunk_size += 1;
		return (1);
	}


	if ((chunk_node->type == ASCEND && chunk_node->prev->type == DESCEND) || (chunk_node->type == DESCEND && chunk_node->prev->type == ASCEND))
	{
		chunk_node->chunk_size += 1;
		return (1);
	}

	return (-1);
}

int	is_chunk_or_edge(int idx, t_stacks *stks)
{
	t_chunk_dll *temp;
	int			total;

	total = 0;
	temp = stks->chunk_stk_b;
	while (idx > total)
	{
		total += temp->chunk_size;
		temp = temp->next;
	}
	if (idx == total) // edge
		return (check_possible_edge(temp, stks));
	else if (idx < total) //in chunk
	{
		temp->chunk_size += 1;
		// chunk 안에 있을 때 위로 가야할지 아래로 가야할지 효율적인 위치 찾기
		if (idx - (total - temp->prev->chunk_size) >= total - idx)
			*move_after_push = total - idx;
		else
			*move_after_push =  -1 * (idx - (total - temp->prev->chunk_size));
		return (1);
	}
	return (-1);
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
int	count_remainder(t_stacks *stks)
{
	int	total;
	t_chunk_dll *temp;

	total = 0;
	temp = stks->chunk_stk_a;
	while (temp->next != stks->chunk_stk_a)
	{
		total += temp->chunk_size;
		temp = temp->next;
	}
	total += temp->chunk_size;
	return (total);
}

void	first_move_to_b(t_stacks *stks, int first_b_num, int *sorted_order)
{
	int	idx;
	int	temp_idx;

	idx = 0;
	while (++idx <= first_b_num)
	{
		temp_idx = -1;
		int test = -1 * sorted_order[idx];
		if (stks->chunk_stk_a->type == test)
		{
			while (++temp_idx < stks->chunk_stk_a->chunk_size)
				ft_push(stks, PB);
			ft_chunk_push(stks, CPB, 1);
		}
		//TODO :: if the upper chunk is bigger (2 * upper chunk size <= head chunk size + second chunk size)
		// than head chunk and the order is suitable(in this case, it should be same type with sorted order),
		// push b the upper one rather than below one.
		else if (stks->chunk_stk_a->next->chunk_size >= stks->chunk_stk_a->chunk_size
			&& stks->chunk_stk_a->next->type == -1 * sorted_order[idx])
		{
			while (++temp_idx < stks->chunk_stk_a->chunk_size)
				ft_rotate(stks, RA);
			ft_chunk_rotate(stks, CRA);
			temp_idx = -1;
			while (++temp_idx < stks->chunk_stk_a->chunk_size)
				ft_push(stks, PB);
			ft_chunk_push(stks, CPB, 1);
		}
		else
		{
			while (++temp_idx < stks->chunk_stk_a->chunk_size - 1)
				ft_rotate(stks, RA);
			temp_idx = -1;
			while (++temp_idx < stks->chunk_stk_a->chunk_size - 1)
			{
				ft_push(stks, PB);
				ft_rotate(stks, RRA);
			}
			ft_push(stks, PB);
			ft_chunk_push(stks, CPB, 0);
		}
	}
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
