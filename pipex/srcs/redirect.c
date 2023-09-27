/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:10:47 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/27 14:03:14 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	redirect_first_child(t_bundle *bundle, int fd[2])
{
	int	infile_fd;

	close(fd[0]);
	infile_fd = open(bundle->filename, O_RDONLY);
	if (infile_fd == -1)
		ft_error("Open Error ", 16, bundle, 1);
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error("Dup2 Error ", 17, bundle, 1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("Dup2 Error ", 18, bundle, 1);
	close(fd[1]);
	close(infile_fd);
}

void	redirect_mid_childs(t_bundle *bundle, int fd[2], int before_fd_read)
{
	close(fd[0]);
	if (dup2(before_fd_read, STDIN_FILENO) == -1)
		ft_error("Dup2 Error ", 19, bundle, 1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		ft_error("Dup2 Error ", 20, bundle, 1);
	close(before_fd_read);
	close(fd[1]);
}

void	redirect_last_child(t_bundle *bundle, int fd[2], int before_fd_read)
{
	int	outfile_fd;

	close(fd[0]);
	close(fd[1]);
	outfile_fd = open(bundle->out_filename, bundle->outfile_flag, 0644);
	if (outfile_fd == -1)
		ft_error("Open Error ", 21, bundle, 1);
	if (dup2(before_fd_read, STDIN_FILENO) == -1)
		ft_error("Dup2 Error ", 22, bundle, 1);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("Dup2 Error ", 23, bundle, 1);
	close(before_fd_read);
	close(outfile_fd);
}
