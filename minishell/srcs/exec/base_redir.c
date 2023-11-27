/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:38:59 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/16 10:50:14 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	base_redir_first_cmd(t_bundle *bundle)
{
	if (bundle->current->pipe)
		if (dup2(bundle->fd[1], STDOUT_FILENO) == -1)
			ft_error(DUP2_ERRMSG, 1);
	if (close(bundle->fd[0]) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	if (close(bundle->fd[1]) == -1)
		ft_error(CLOSE_ERRMSG, 1);
}

void	base_redir_mid_cmd(t_bundle *bundle, int before_fd_read)
{
	if (dup2(before_fd_read, STDIN_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (dup2(bundle->fd[1], STDOUT_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(before_fd_read) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	if (close(bundle->fd[0]) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	if (close(bundle->fd[1]) == -1)
		ft_error(CLOSE_ERRMSG, 1);
}

void	base_redir_last_cmd(t_bundle *bundle, int before_fd_read)
{
	if (bundle->current && bundle->current->cmd
		&& bundle->current->cmd->simple_cmd->cmd_path)
		if (dup2(before_fd_read, STDIN_FILENO) == -1)
			ft_error(DUP2_ERRMSG, 1);
	if (close(before_fd_read) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	if (close(bundle->fd[0]) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	if (close(bundle->fd[1]) == -1)
		ft_error(CLOSE_ERRMSG, 1);
}
