/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:48:30 by hyuim             #+#    #+#             */
/*   Updated: 2023/08/11 21:49:11 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void ft_swap(t_stacks *stacks, char *cmd)
{
	int	temp;

	if (cmd == "sa")
	{
		temp = stacks->stk_a->value;
		stacks->stk_a->value = stacks->stk_a->next->value;
		stacks->stk_a->next->value = temp;
	}
	else if (cmd == "sb")
	{
		temp = stacks->stk_b->value;
		stacks->stk_b->value = stacks->stk_b->next->value;
		stacks->stk_b->next->value = temp;
	}
	ft_lstadd_back(&(stacks->cmd_list), ft_lstnew(cmd));
}