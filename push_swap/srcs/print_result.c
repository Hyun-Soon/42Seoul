/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_result.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:06:17 by soon              #+#    #+#             */
/*   Updated: 2023/09/11 13:43:43 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_result(t_stacks *stks)
{
	t_list	*temp;

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

void	optimize_cmds(t_stacks *stks, int *flag)
{
	t_list	*temp;
	int		cmds_sum;

	temp = stks->cmd_list;
	*flag = 0;
	while (temp->next)
	{
		cmds_sum = temp->content + temp->next->content;
		if (cmds_sum == 0)
		{
			ft_lstdelone(temp->next);
			ft_lstdelone(temp);
			*flag = 1;
			return ;
		}
		else if (cmds_sum == SS || cmds_sum == RR || cmds_sum == RRR)
		{
			merge_cmd(temp, cmds_sum, flag);
			return ;
		}
		temp = temp->next;
	}
}

void	merge_cmd(t_list *cmd_node, int cmd, int *flag)
{
	t_list	*new_cmd;
	t_list	*temp_prev;
	t_list	*temp_next;

	temp_prev = cmd_node->prev;
	temp_next = cmd_node->next->next;
	ft_lstdelone(cmd_node->next);
	ft_lstdelone(cmd_node);
	new_cmd = ft_lstnew(cmd);
	temp_prev->next = new_cmd;
	new_cmd->prev = temp_prev;
	new_cmd->next = temp_next;
	temp_next->prev = new_cmd;
	*flag = 1;
}
