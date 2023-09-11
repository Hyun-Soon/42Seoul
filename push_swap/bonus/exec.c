/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:16:27 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/11 17:17:30 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	exec_cmd(t_stacks *stks, char *cmd)
{
	if (!ft_strcmp("sa\n", cmd) || !ft_strcmp("sb\n", cmd)
		|| !ft_strcmp("ss\n", cmd))
		exec_cmd_swap(stks, cmd);
	else if (!ft_strcmp("pa\n", cmd) || !ft_strcmp("pb\n", cmd))
		exec_cmd_push(stks, cmd);
	else if (!ft_strcmp("ra\n", cmd) || !ft_strcmp("rb\n", cmd)
		|| !ft_strcmp("rr\n", cmd))
		exec_cmd_rotate(stks, cmd);
	else if (!ft_strcmp("rra\n", cmd) || !ft_strcmp("rrb\n", cmd)
		|| !ft_strcmp("rrr\n", cmd))
		exec_cmd_reverse_rotate(stks, cmd);
	else
		ft_error(ERROR, 1);
}

void	exec_cmd_swap(t_stacks *stks, char *cmd)
{
	if (!ft_strcmp("sa\n", cmd))
	{
		if (stks->stk_a != stks->stk_a->next)
		{
			ft_swap(stks, SA);
			return ;
		}
	}
	else if (!ft_strcmp("sb\n", cmd))
	{
		if (stks->stk_b != stks->stk_b->next)
		{
			ft_swap(stks, SB);
			return ;
		}
	}
	else if (!ft_strcmp("ss\n", cmd))
	{
		exec_cmd_swap(stks, "sa\n");
		exec_cmd_swap(stks, "sb\n");
		return ;
	}
	ft_error(ERROR, 1);
}

void	exec_cmd_push(t_stacks *stks, char *cmd)
{
	if (!ft_strcmp("pa\n", cmd))
	{
		if (stks->stk_b)
		{
			ft_push(stks, PA);
			return ;
		}
	}
	else if (!ft_strcmp("pb\n", cmd))
	{
		if (stks->stk_a)
		{
			ft_push(stks, PB);
			return ;
		}
	}
	ft_error(ERROR, 1);
}

void	exec_cmd_rotate(t_stacks *stks, char *cmd)
{
	if (!ft_strcmp("ra\n", cmd))
	{
		if (stks->stk_a)
		{
			ft_rotate(stks, RA);
			return ;
		}
	}
	else if (!ft_strcmp("rb\n", cmd))
	{
		if (stks->stk_b)
		{
			ft_rotate(stks, RB);
			return ;
		}
	}
	else if (!ft_strcmp("rr\n", cmd))
	{
		exec_cmd_rotate(stks, "ra\n");
		exec_cmd_rotate(stks, "rb\n");
		return ;
	}
	ft_error(ERROR, 1);
}

void	exec_cmd_reverse_rotate(t_stacks *stks, char *cmd)
{
	if (!ft_strcmp("rra\n", cmd))
	{
		if (stks->stk_a)
		{
			ft_rotate(stks, RRA);
			return ;
		}
	}
	else if (!ft_strcmp("rrb\n", cmd))
	{
		if (stks->stk_b)
		{
			ft_rotate(stks, RRB);
			return ;
		}
	}
	else if (!ft_strcmp("rrr\n", cmd))
	{
		exec_cmd_reverse_rotate(stks, "rra\n");
		exec_cmd_reverse_rotate(stks, "rrb\n");
		return ;
	}
	ft_error(ERROR, 1);
}
