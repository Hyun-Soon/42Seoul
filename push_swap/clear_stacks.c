/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soon <soon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:19:15 by soon              #+#    #+#             */
/*   Updated: 2023/09/10 19:19:44 by soon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_stackclear(t_dll *stk)
{
	t_dll	*temp;

	while (stk)
	{
		temp = stk->next;
		free(stk);
		stk = temp;
	}
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
