/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 15:09:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/10 18:17:11 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// no param -> do not display anything
// error -> display "Error\n"
// error : not integers, bigger than integer, duplicates

#include "push_swap.h"
#include <stdio.h> /////////////////////////////////

int main(int argc, char **argv)
{
	int		*inp_list;
	t_dll	*head_a;
	t_dll	*head_b;
	t_st	*information;

	inp_list = parse_input(argc, argv);
	make_stacks(argc - 1, &head_a, &head_b, inp_list);
	information = make_inform_stack(argc - 1, inp_list);

	// printf("%d\n", inp_list[0]);
	// printf("%d\n", inp_list[1]);
	// printf("%d\n", inp_list[2]);

	// printf("stk_a[-1] : %d\n", head_a->prev->value);
	// printf("stk_a[0] : %d\n", head_a->value);
	// printf("stk_a[1] : %d\n", head_a->next->value);
	// printf("stk_a[2] : %d\n", head_a->next->next->value);

	//printf("%d, %d\n", information->prev->type, information->prev->chunk_size);
	// printf("%d, %d\n", information->type, information->chunk_size);
	// printf("%d, %d\n", information->next->type, information->next->chunk_size);
	// printf("%d, %d\n", information->next->next->type, information->next->next->chunk_size);

	/*
	int i = 0;
	t_st *temp = information;
	while (temp->next != information)
	{
		printf("%d\n", temp->chunk_size);
		temp = temp->next;
		i++;
	}
	printf("%d\n", temp->chunk_size);
	return (0);
	*/
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

void	first_node(t_st **head, int chunk_size)
{
	*head = (t_st *)malloc(sizeof(t_st));
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

void	append_node(t_st **head, int chunk_size)
{
	t_st	*temp;
	t_st	*new_node;

	printf("append node exec\n");
	if (!*head)
	{
		first_node(head, chunk_size);
		return ;
	}
	temp = *head;
	while (temp->next && temp->next != *head)
		temp = temp->next;
	new_node = (t_st *)malloc(sizeof(t_st));
	if (!new_node)
		ft_error(ERROR, 2);
	temp->next = new_node;
	new_node->prev = temp;
	new_node->next = *head;
	if (chunk_size > 0)
	{
		new_node->chunk_size = chunk_size;
		new_node->type = ASCEND;
		return ;
	}
	new_node->chunk_size = -chunk_size;
	new_node->type = DESCEND;
}

t_st	*make_inform_stack(int inp_num, int *inp_list)
{
	t_st	*head;
	int		idx;
	int		chunk_size;

	head = NULL;
	idx = 0;
	while (check_des_asc(&idx, inp_num, inp_list, &chunk_size))
		append_node(&head, chunk_size);
	return (head);
}

void	make_filled_stack(t_dll **head_a, int *inp_list, int inp_num)
{
	int		idx;
	t_dll	*temp;

	*head_a = (t_dll *)malloc(sizeof(t_dll));
	idx = -1;
	(*head_a)->value = inp_list[++idx];
	temp = *head_a;
	while(++idx < inp_num)
	{
		temp->next = (t_dll *)malloc(sizeof(t_dll));
		temp->next->prev = temp;
		temp = temp->next;
		temp->value = inp_list[idx];
	}
	temp->next = *head_a;
	(*head_a)->prev = temp;
}

void	make_empty_stack(t_dll **head_b, int inp_num)
{
	int		idx;
	t_dll	*temp;

	*head_b = (t_dll *)malloc(sizeof(t_dll));
	idx = 0;
	temp = *head_b;
	while (++idx < inp_num)
	{
		temp->next = (t_dll *)malloc(sizeof(t_dll));
		temp->next->prev = temp;
		temp = temp->next;
	}
	temp->next = *head_b;
	(*head_b)->prev = temp;
}

void	make_stacks(int inp_num, t_dll **head_a, t_dll **head_b, int *inp_list)
{
	make_filled_stack(head_a, inp_list, inp_num);
	make_empty_stack(head_b, inp_num);
}
t_dll	*make_nodes(int val)
{
	t_dll	*addr;

	addr = (t_dll *)malloc(sizeof(t_dll));
	addr->value = val;
	return (addr);
}

