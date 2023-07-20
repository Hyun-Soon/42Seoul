/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:09:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/20 21:59:29 by hyuim            ###   ########.fr       */
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

	atexit(check);
	inp_list_size = 0;
	inp_list = parse_input(argc, argv, &inp_list_size);
	// system("leaks --list a.out");
	if (inp_list_size <= 1)
		exit(0);
	for (int i = 0; i < inp_list_size; i++)
		printf("%d\n", inp_list[i]);
	exit(0);
}
	// for (int i = 0; i < inp_list_size; i++)
	// {
	// 	printf("%d\n", inp_list[i]);
	// }
	// if (argc - 1 <= 5)
	// 	exception(argc - 1, inp_list);
	// merge(argc, inp_list);

	


	// printf("%d\n", inp_list[0]);
	// printf("%d\n", inp_list[1]);
	// printf("%d\n", inp_list[2]);

	// printf("stk_a[-1] : %d\n", stk_a->prev->value);
	// printf("stk_a[0] : %d\n", stk_a->value);
	// printf("stk_a[1] : %d\n", stk_a->next->value);
	// printf("stk_a[2] : %d\n", stk_a->next->next->value);

	//printf("%d, %d\n", chunk_stk->prev->type, chunk_stk->prev->chunk_size);
	// printf("%d, %d\n", chunk_stk->type, chunk_stk->chunk_size);
	// printf("%d, %d\n", chunk_stk->next->type, chunk_stk->next->chunk_size);
	// printf("%d, %d\n", chunk_stk->next->next->type, chunk_stk->next->next->chunk_size);

////////////////////////////////////////////////////
	// int i = 0;
	// t_dll *temp = chunk_stk;
	// while (temp->next != chunk_stk)
	// {
	// 	printf("%d\n", temp->chunk_size);
	// 	temp = temp->next;
	// 	i++;
	// }
	// printf("%d\n", temp->chunk_size);
	// return (0);
/////////////////////////////////////////////////////

// void	sort_2args(int *inp_list)
// {
// 	if (inp_list[0] > inp_list[1])
// 		ft_printf("sa\n");
// 	exit(0);
// }

// void	sort_3args(int *inp_list)
// {
// 	if (inp_list[0] < inp_list[1] && inp_list[1] > inp_list[2])
// 		ft_printf("ra\nsa\nrra\n");
// 	else if (inp_list[0] > inp_list[1] && inp_list[0] < inp_list[2])
// 		ft_printf("sa\n");
// 	else if (inp_list[0] > inp_list[2] && inp_list[0] < inp_list[1])
// 		ft_printf("ra\nra\n");
// 	else if (inp_list[0] > inp_list[2] && inp_list[2] > inp_list[1])
// 		ft_printf("ra\n");
// 	else if (inp_list[0] > inp_list[1] && inp_list[1] > inp_list[2])
// 		ft_printf("sa\nrra\n");
// }

// void	sort(int inp_num, int *sorted)
// {
// 	int	i;
// 	int	j;
// 	int	temp;

// 	i = -1;
// 	while (++i < 2)
// 	{
// 		j = inp_num;
// 		while (--j > i)
// 		{
// 			if (sorted[j] < sorted[j - 1])
// 			{
// 				temp = sorted[j];
// 				sorted[j] = sorted[j - 1];
// 				sorted[j - 1] = temp;
// 			}
// 		}
// 	}
// }

// void	sort_5args(int inp_num, int *inp_list)
// {
// 	int	*sorted;
// 	int	iter;
// 	int	flag;
// 	int	idx;
// 	int	idx2;
// 	int	idx3;
// 	int	temp;
// 	int	*new;

// 	sorted = (int *)malloc(sizeof(int) * (inp_num));
// 	ft_memcpy(sorted, inp_list, inp_num * 4);
// 	sort(inp_num, sorted);
// 	flag = inp_num - 3;
// 	idx = 0;
// 	if (flag == 1)
// 	{
// 		while (inp_list[idx] != sorted[0])
// 		{
// 			idx++;
// 			ft_printf("ra\n");
// 		}
// 		ft_printf("pb\n");
// 		new = malloc
// 	}
	
// 	if (flag == 2)
// 	{
// 			while (inp_list[idx] != sorted[0] && inp_list[idx] != sorted[1])
// 			{
// 				idx++;
// 				ft_printf("ra\n");
// 			}
// 			temp = inp_list[idx];
// 			ft_printf("pb\n");
// 			idx++;
// 			ft_printf("ra\n");
// 			while (inp_list[idx] != sorted[0] && inp_list[idx] != sorted[1])
// 			{
// 				idx++;
// 				ft_printf("ra\n");
// 			}
// 			ft_printf("pb\n");
// 			if (inp_list[idx] < temp)
// 				ft_printf("sb\n");
// 			new = (int *)malloc(sizeof(int) * 3);
// 			idx2 = 0;
// 			idx3 = 0;
// 			while (idx2 < inp_num)
// 			{
// 				if (inp_list[idx2] != inp_list[idx] && inp_list[idx2] != temp)
// 				{
// 					new[idx3] = inp_list[idx2];
// 					idx3++;
// 				}
// 				idx2++;
// 			}
// 			sort_3args(new);

// 	}

	
// }

// void	exception(int inp_num, int *inp_list)
// {
// 	if (inp_num == 2)
// 		sort_2args(inp_list);
// 	else if (inp_num == 3)
// 		sort_3args(inp_list);
// 	else
// 		sort_5args(inp_num, inp_list);
// 	exit(0);
// }

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
	stacks->command = NULL;

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

	if (total_size <= 5)
		return (total_size);
	n = 3;
	while (total_size > n)
		n *= 9;
	return (n / 9);
	//근데 inp_list len이 5이하일 때도 해줘야 할듯?
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

void	first_node(t_dll **head, int chunk_size)
{
	*head = (t_dll *)malloc(sizeof(t_dll));
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

void	append_node(t_dll **head, int chunk_size)
{
	t_dll	*temp;
	t_dll	*new_node;

	if (!*head)
	{
		first_node(head, chunk_size);
		return ;
	}
	temp = *head;
	while (temp->next && temp->next != *head)
		temp = temp->next;
	new_node = (t_dll *)malloc(sizeof(t_dll));
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


t_dll	*make_chunk_stack_a(int inp_num, int *inp_list, t_stacks *stacks)
{
	t_dll	*head;
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