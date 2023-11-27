/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:44:26 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/23 14:21:41 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	check_point_slash(char *cmd_path)
{
	if (ft_strlen(cmd_path) >= 2 && cmd_path[0] == '.' && cmd_path[1] == '/')
	{
		if (access(cmd_path, F_OK) != 0)
		{
			write(2, cmd_path, ft_strlen(cmd_path));
			write(2, ": command not found\n", 20);
			exit(127);
		}
		ft_error(cmd_path + 2, 126);
	}
	write(2, cmd_path, ft_strlen(cmd_path));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	select_err_msg(char *cmd_path)
{
	struct stat	st;

	if (stat(cmd_path, &st) != -1)
	{
		if ((st.st_mode & S_IFDIR) == S_IFDIR)
		{
			write(2, cmd_path, ft_strlen(cmd_path));
			write(2, ": is a directory\n", 17);
			if ((ft_strlen(cmd_path) >= 2 && cmd_path[0] == '.' \
				&& cmd_path[1] == '/')
				|| (ft_strlen(cmd_path) >= 1 && cmd_path[0] == '/'))
				exit(126);
			exit(127);
		}
		if (access(cmd_path, X_OK) != 0)
		{
			perror(NULL);
			exit(126);
		}
	}
	check_point_slash(cmd_path);
}

void	print_cmd_not_found_err(t_simple_cmd *simple_cmd)
{
	write(2, simple_cmd->cmd_path, ft_strlen(simple_cmd->cmd_path));
	write(2, ": command not found\n", 20);
	exit(127);
}
