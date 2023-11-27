/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 21:19:25 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/17 21:55:56 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_current_file(t_bundle *bundle, int cmd_idx)
{
	int	idx;

	if (cmd_idx > 0 && bundle->current_cnt)
	{
		idx = -1;
		while (++idx < bundle->current_cnt->cnt)
			bundle->current_filename = bundle->current_filename->next;
		bundle->current_cnt = bundle->current_cnt->next;
	}
	else
	{
		bundle->current_filename = bundle->hrdc_filename_list;
		bundle->current_cnt = bundle->hrdc_cnt_list;
	}
}

int	exec_recur(t_pipe *root, t_bundle *bundle, int before_fd_read, int cmd_idx)
{
	int	pid;

	if (pipe(bundle->fd) == -1)
		return (-1);
	set_current_file(bundle, cmd_idx);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0 && root->cmd)
	{
		bundle->current = root;
		if (exec_cmd(root->cmd, bundle, before_fd_read, cmd_idx) == -1)
			return (-1);
		return (0);
	}
	if (root->pipe == NULL)
		bundle->last_pid = pid;
	close(bundle->fd[1]);
	if (pid > 0 && root->pipe)
		if (exec_recur(root->pipe, bundle, bundle->fd[0], cmd_idx + 1) == -1)
			return (-1);
	close(bundle->fd[0]);
	close(before_fd_read);
	return (0);
}

int	exec_cmd(t_cmd *cmd, t_bundle *bundle, int before_fd_read, int cmd_idx)
{
	if (cmd_idx == 0)
		base_redir_first_cmd(bundle);
	else if (cmd_idx == bundle->fork_cnt - 1)
		base_redir_last_cmd(bundle, before_fd_read);
	else
		base_redir_mid_cmd(bundle, before_fd_read);
	if (cmd->redirect_s)
		if (exec_redirect_s_recur(cmd->redirect_s, bundle) == -1)
			exit(1);
	if (bundle->cmd_cnt == 0)
		exit(0);
	if (!bundle->err_flag && cmd->simple_cmd->cmd_path)
		exec_simple_cmd(cmd->simple_cmd, bundle);
	exit(0);
}

int	exec_redirect_s_recur(t_redirect_s *redirect_s, t_bundle *bundle)
{
	if (redirect_s && redirect_s->redirect)
		if (exec_redirect(redirect_s->redirect, bundle) == -1)
			return (-1);
	if (redirect_s && redirect_s->redirect_s)
		if (exec_redirect_s_recur(redirect_s->redirect_s, bundle) == -1)
			return (-1);
	return (0);
}

void	exec_simple_cmd(t_simple_cmd *simple_cmd, t_bundle *bundle)
{
	char	**parsed_path;

	if (is_builtin(simple_cmd->cmd_path))
		exit(exec_builtin(simple_cmd->cmd_path, simple_cmd->cmd_argv, bundle));
	if (!access(simple_cmd->cmd_path, F_OK))
		if (execve(simple_cmd->cmd_path,
				simple_cmd->cmd_argv, bundle->envp) == -1)
			select_err_msg(simple_cmd->cmd_path);
	parsed_path = get_path(bundle->envp);
	if (!parsed_path)
		print_cmd_not_found_err(simple_cmd);
	exec_with_new_path(parsed_path, -1, simple_cmd, bundle);
	free_2d_malloced_str(parsed_path);
	select_err_msg(simple_cmd->cmd_path);
}
