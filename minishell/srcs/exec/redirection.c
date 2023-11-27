/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:25:40 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/17 21:30:38 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	redir_left(char *filename)
{
	int	infile_fd;

	if (access(filename, F_OK))
	{
		write(2, filename, ft_strlen(filename));
		write(2, ": No such file or directory\n", 28);
		return (-1);
	}
	infile_fd = open(filename, O_RDONLY);
	if (infile_fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(infile_fd) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	return (0);
}

int	redir_right(char *filename)
{
	int	outfile_fd;
	int	open_flag;

	open_flag = O_RDWR | O_CREAT | O_TRUNC;
	outfile_fd = open(filename, open_flag, 0644);
	if (outfile_fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(outfile_fd) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	return (0);
}

int	redir_two_left(t_bundle *bundle)
{
	int	infile_fd;
	int	open_flag;

	open_flag = O_RDWR | O_CREAT;
	infile_fd = open(bundle->current_filename->content, open_flag, 0644);
	if (infile_fd == -1)
	{
		perror(OPEN_ERRMSG);
		return (-1);
	}
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(infile_fd) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	bundle->current_filename = bundle->current_filename->next;
	return (0);
}

int	redir_two_right(char *filename)
{
	int	outfile_fd;
	int	open_flag;

	open_flag = O_RDWR | O_CREAT | O_APPEND;
	outfile_fd = open(filename, open_flag, 0644);
	if (outfile_fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error(DUP2_ERRMSG, 1);
	if (close(outfile_fd) == -1)
		ft_error(CLOSE_ERRMSG, 1);
	return (0);
}

int	exec_redirect(t_redirect *redirect, t_bundle *bundle)
{
	if (redirect->type == REDIR_LEFT)
		return (redir_left(redirect->filename));
	else if (redirect->type == REDIR_RIGHT)
		return (redir_right(redirect->filename));
	else if (redirect->type == REDIR_TWO_LEFT)
		return (redir_two_left(bundle));
	else if (redirect->type == REDIR_TWO_RIGHT)
		return (redir_two_right(redirect->filename));
	return (0);
}
