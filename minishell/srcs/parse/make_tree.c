/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 19:25:06 by hgu               #+#    #+#             */
/*   Updated: 2023/11/16 14:21:31 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	copy_strings(char **new, char **old, int cnt)
{
	int	idx;

	idx = 0;
	while (idx < cnt)
	{
		new[idx] = old[idx];
		idx++;
	}
}

void	error_pipe(t_pipe *pipe, t_bundle *bundle)
{
	pipe->flag = 0;
	if (pipe->cmd->redirect_s->redirect->filename == NULL)
	{
		if (pipe->cmd->simple_cmd->cmd_path != NULL)
		{
			free_cmd(pipe->cmd);
			bundle->cmd_cnt -= 1;
			pipe->cmd = NULL;
		}
	}
}

void	set_pipe_node(t_token *tmp, t_pipe **pipe)
{
	free(tmp->value);
	(*pipe)->pipe = make_pipe();
	*pipe = (*pipe)->pipe;
}

void	check_err_and_make_cmd(t_bundle *bundle, t_token *tmp, t_pipe *pipe)
{
	free(tmp->value);
	error_pipe(pipe, bundle);
	if (tmp->type == PIPE)
		pipe->cmd = make_cmd();
}

t_pipe	*make_tree(t_bundle *bundle, t_token *tmp)
{
	t_pipe	*pipe_head;
	t_pipe	*pipe;

	pipe_head = make_pipe();
	pipe = pipe_head;
	while (tmp)
	{
		if ((tmp->type == PIPE || tmp->next == NULL) && pipe->flag >= 1)
			check_err_and_make_cmd(bundle, tmp, pipe);
		else if (tmp->type == PIPE)
			set_pipe_node(tmp, &pipe);
		else if (tmp->type >= REDIR_LEFT && tmp->type <= REDIR_TWO_RIGHT)
		{
			make_redirect_s(&(pipe->cmd->redirect_s), tmp, pipe, bundle);
			tmp = tmp->next;
			if (tmp == NULL)
				break ;
		}
		else
			make_simple_cmd(pipe->cmd, tmp, bundle);
		if (tmp->expansion_fail != NULL)
			free(tmp->expansion_fail);
		tmp = tmp->next;
	}
	return (pipe_head);
}
