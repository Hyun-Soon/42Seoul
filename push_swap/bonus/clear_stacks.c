/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:19:15 by soon              #+#    #+#             */
/*   Updated: 2023/09/11 13:20:34 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_stackclear(t_dll *stk)
{
	t_dll	*temp1;
	t_dll	*temp2;

	temp1 = stk;
	while (temp1->next != stk)
	{
		temp2 = temp1->next;
		free(temp1);
		temp1 = temp2;
	}
	free(temp1);
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
