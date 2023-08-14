/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:09:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/08/14 21:51:11 by hyuim            ###   ########.fr       */
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

	//atexit(check);
	inp_list_size = 0;
	inp_list = parse_input(argc, argv, &inp_list_size);
	// system("leaks --list a.out");
	if (inp_list_size <= 1)
		exit(0);
	// for (int i = 0; i < inp_list_size; i++)
	// 	printf("%d\n", inp_list[i]);
	// printf("\n");

	t_stacks	stks;
	make_stacks(&stks, inp_list_size, inp_list);
	t_dll	*temp_a = stks.stk_a;
	while (temp_a->next != stks.stk_a)
	{
		printf("%d\n", temp_a->value);
		temp_a = temp_a->next;
	}
	printf("%d\n", temp_a->value);


	t_chunk_dll	*temp_cnk_a = stks.chunk_stk_a;
	while (temp_cnk_a->next != stks.chunk_stk_a)
	{
		printf("cnk size : %d\n", temp_cnk_a->chunk_size);
		printf("cnk type : %d\n", temp_cnk_a->type);
		temp_cnk_a = temp_cnk_a->next;
	}
	printf("cnk size : %d\n", temp_cnk_a->chunk_size);
	printf("cnk type : %d\n", temp_cnk_a->type);
	printf("\n");

	printf("initial chunk size : %d\n", stks.initial_chunk_stk_size);
	printf("\n");

	int	first_b_num = get_triangle_nums(stks.initial_chunk_stk_size);
	printf("first_b_num : %d\n", first_b_num);
	printf("\n");

	//*****************b에  정정렬렬할  모모양  알알아아내내기기*************************
	int	exp = 0;
	int	offset = ft_pow(3, exp);
	sorted_order[1] = 1;
	while (1 + offset < first_b_num)
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


	for (int i = 1; i <= first_b_num; i++)
		printf("%d\n", sorted_order[i]);

	////////////////////////////////////////////////////////////////////////
	exit(0);
}

// void	swap(t_dll **stk, t_list **cmd_list, char *cmd)
// {
// 	if (*stk && (*stk)->next != *stk)
// 	{
		
// 	}
// }

t_dll	*pop(t_dll **stk)
{
	t_dll	*temp;
	if (!*stk)
		return (NULL);
	if ((*stk)->next == *stk && (*stk)->prev == *stk)
	{
		temp = *stk;
		*stk = NULL;
		return (temp);
	}
	temp = *stk;
	(*stk)->prev->next = (*stk)->next;
	(*stk)->next->prev = (*stk)->prev;
	temp->next = temp;
	temp->prev = temp;
	return (temp);
}

t_chunk_dll	*cpop(t_chunk_dll **stk)
{
	t_chunk_dll	*temp;
	if (!*stk)
		return (NULL);
	if ((*stk)->next == *stk && (*stk)->prev == *stk)
	{
		temp = *stk;
		*stk = NULL;
		return (temp);
	}
	temp = *stk;
	(*stk)->prev->next = (*stk)->next;
	(*stk)->next->prev = (*stk)->prev;
	temp->next = temp;
	temp->prev = temp;
	return (temp);
}

void	push(t_dll *node, t_dll **stk)
{
	if (!*stk)
	{
		*stk = node;
		return;
	}
	node->next = *stk;
	node->prev = (*stk)->prev;
	(*stk)->prev->next = node;
	(*stk)->prev = node;
	*stk = node;
}

void	cpush(t_chunk_dll *node, t_chunk_dll **stk)
{
	if (!*stk)
	{
		*stk = node;
		return;
	}
	node->next = *stk;
	node->prev = (*stk)->prev;
	(*stk)->prev->next = node;
	(*stk)->prev = node;
	*stk = node;
}

void	merge(int argc, int *inp_list)
{
	t_stacks	stacks;

	make_stacks(&stacks, argc - 1, inp_list);
	free(inp_list);
	// TODO :: 아랫줄 -> 3, 5, 그 이상일 때 구현하기
	//make_sorted_chunks_in_b(get_triangle_nums(chunk_stk_a->total_size));
}

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

void	first_node(t_chunk_dll **head, int chunk_size)
{
	*head = (t_chunk_dll *)malloc(sizeof(t_chunk_dll));
	if (!*head)
		ft_error(ERROR, 2);
	(*head)->next = *head;
	(*head)->prev = *head;
	if (chunk_size > 0)
	{
		(*head)->chunk_size = chunk_size;
		(*head)->type = ASCEND;
		return ;
	}
	(*head)->chunk_size = -chunk_size;
	(*head)->type = DESCEND;
}

void	append_node(t_chunk_dll **head, int chunk_size)
{
	t_chunk_dll	*temp;
	t_chunk_dll	*new_node;

	if (!(*head))
	{
		first_node(head, chunk_size);
		return ;
	}
	temp = *head;
	while (temp->next && temp->next != *head)
		temp = temp->next;
	new_node = (t_chunk_dll *)malloc(sizeof(t_chunk_dll));
	if (!new_node)
		ft_error(ERROR, 2);
	temp->next = new_node;
	new_node->prev = temp;
	new_node->next = *head;
	if (chunk_size >= 0)
	{
		new_node->chunk_size = chunk_size;
		new_node->type = ASCEND;
		return ;
	}
	new_node->chunk_size = -chunk_size;
	new_node->type = DESCEND;
}


t_chunk_dll	*make_chunk_stack_a(int inp_num, int *inp_list, t_stacks *stacks)
{
	t_chunk_dll	*head;
	int		idx;
	int		chunk_size;
	int		stk_size;

	head = NULL;
	idx = 0;
	stk_size = 0;
	while (check_des_asc(&idx, inp_num, inp_list, &chunk_size))
	{
		append_node(&head, chunk_size);
		stk_size++;
	}
	stacks->initial_chunk_stk_size = stk_size;
	return (head);
}


t_dll	*make_stack_a(int *inp_list, int inp_num)
{
	int		idx;
	t_dll	*temp;
	t_dll	*head;
	
	head= (t_dll *)malloc(sizeof(t_dll));
	if (!head)
		ft_error(ERROR, 2);
	idx = -1;
	head->value = inp_list[++idx];
	temp = head;
	while(++idx < inp_num)
	{
		temp->next = (t_dll *)malloc(sizeof(t_dll));
		temp->next->prev = temp;
		temp = temp->next;
		temp->value = inp_list[idx];
	}
	temp->next = head;
	head->prev = temp;
	return (head);
}