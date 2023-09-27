/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:05:41 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/27 20:01:48 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	exec_cmd(t_bundle *bundle, char *envp[], int idx)
{
	int		path_idx;
	char	*path_plus_cmd;

	execve(bundle->cmd_args[idx][0], bundle->cmd_args[idx], envp);
	path_idx = -1;
	while (bundle->parsed_path[++path_idx])
	{
		path_plus_cmd = ft_strjoin(bundle->parsed_path[path_idx], "/");
		path_plus_cmd = ft_strjoin(path_plus_cmd, bundle->cmd_args[idx][0]);
		execve(path_plus_cmd, bundle->cmd_args[idx], envp);
	}
	ft_error("Cmd not found Error ", 13, bundle, 1);
}

void	exec_one_cmd(t_bundle *bundle, char *envp[])
{
	int	infile_fd;
	int	outfile_fd;
	int	pid;

	infile_fd = open(bundle->filename, O_RDONLY);
	if (infile_fd == -1)
		ft_error("Open Error ", 9, bundle, 1);
	outfile_fd = open(bundle->out_filename, bundle->outfile_flag, 0644);
	if (outfile_fd == -1)
		ft_error("Open Error ", 10, bundle, 1);
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		ft_error("Dup2 Error ", 11, bundle, 1);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		ft_error("Dup2 Error ", 12, bundle, 1);
	close(infile_fd);
	close(outfile_fd);
	pid = fork();
	if (pid < 0)
		ft_error("Fork Error ", 13, bundle, 1);
	if (pid == 0)
		exec_cmd(bundle, envp, 0);
}

void	exec_multiple_cmds(t_bundle *bundle, char *envp[], int idx)
{
	int	fd[2];
	int	before_fd_read;
	int	pid;

	while (++idx < bundle->cmd_cnts)
	{
		before_fd_read = fd[0];
		if (pipe(fd) == -1)
			ft_error("Pipe Error ", 14, bundle, 1);
		pid = fork();
		if (pid < 0)
			ft_error("Fork Error ", 15, bundle, 1);
		if (pid == 0)
		{
			if (idx == 0)
				redirect_first_child(bundle, fd);
			else if (idx == bundle->cmd_cnts - 1)
				redirect_last_child(bundle, fd, before_fd_read);
			else
				redirect_mid_childs(bundle, fd, before_fd_read);
			exec_cmd(bundle, envp, idx);
		}
		close(fd[1]);
	}
}
