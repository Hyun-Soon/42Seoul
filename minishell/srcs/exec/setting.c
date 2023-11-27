/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:39:31 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 22:34:48 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	setting(int argc, char *argv[], t_bundle *bundle, char *envp[])
{
	(void)argc;
	(void)argv;
	cp_envp(bundle, envp);
	rl_catch_signals = 0;
}

void	get_fork_cnt(t_bundle *bundle, t_pipe *root)
{
	int	fork_cnt;

	fork_cnt = 0;
	while (root)
	{
		fork_cnt++;
		root = root->pipe;
	}
	bundle->fork_cnt = fork_cnt;
}

void	set_exit_status(t_bundle *bundle)
{
	int	exit_result;
	int	finished_pid;

	finished_pid = wait(&exit_result);
	if (finished_pid == bundle->last_pid)
	{
		if (WIFSIGNALED(exit_result))
			g_exit_status = 128 + WTERMSIG(exit_result);
		else
			g_exit_status = WEXITSTATUS(exit_result);
	}
}

t_list_hrdc	*ft_lstnew_hrdc(void)
{
	t_list_hrdc	*new_list;

	new_list = (t_list_hrdc *)malloc(sizeof(t_list_hrdc));
	if (!new_list)
		return (NULL);
	new_list->cnt = 0;
	new_list->next = NULL;
	return (new_list);
}

void	ft_lstadd_back_hrdc(t_list_hrdc **lst, t_list_hrdc *new)
{
	t_list_hrdc	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return ;
}
