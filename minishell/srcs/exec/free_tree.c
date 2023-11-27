/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:49:57 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/14 20:46:01 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_tree(t_pipe *root)
{
	if (root && root->pipe)
		free_tree(root->pipe);
	if (root && root->cmd)
		free_cmd(root->cmd);
	free(root);
}

void	free_cmd(t_cmd *cmd)
{
	int	idx;

	free(cmd->simple_cmd->cmd_path);
	idx = 0;
	if (cmd->simple_cmd->cmd_argv)
		while (cmd->simple_cmd->cmd_argv[++idx])
			free(cmd->simple_cmd->cmd_argv[idx]);
	free(cmd->simple_cmd->cmd_argv);
	free(cmd->simple_cmd);
	if (cmd->redirect_s)
		free_redirect_s(cmd->redirect_s);
	free(cmd);
}

void	free_redirect_s(t_redirect_s *redirect_s)
{
	if (redirect_s->redirect_s)
		free_redirect_s(redirect_s->redirect_s);
	if (redirect_s->redirect)
		free_redirect(redirect_s->redirect);
	free(redirect_s);
}

void	free_redirect(t_redirect *redirect)
{
	if (redirect->filename)
		free(redirect->filename);
	free(redirect);
}

void	free_token(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		free(temp);
		token = token->next;
		temp = token;
	}
}
