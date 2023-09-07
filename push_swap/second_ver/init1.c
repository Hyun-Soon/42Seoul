/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:48:44 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/07 17:16:39 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
