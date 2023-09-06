/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:48:44 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/04 20:59:32 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	(*head)->prev = new_node;
	set_chunk_node(new_node, chunk_size);
	// if (chunk_size >= 0)
	// {
	// 	new_node->chunk_size = chunk_size;
	// 	new_node->type = ASCEND;
	// 	return ;
	// }
	// new_node->chunk_size = -chunk_size;
	// new_node->type = DESCEND;
}

void	set_chunk_node(t_chunk_dll *new_node, int chunk_size)
{
	if (chunk_size >= 0)
	{
		new_node->chunk_size = chunk_size;
		new_node->type = ASCEND;
	}
	else
	{
		new_node->chunk_size = -chunk_size;
		new_node->type = DESCEND;
	}
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
	
	head = (t_dll *)malloc(sizeof(t_dll));
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
