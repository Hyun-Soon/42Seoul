/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:35:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 22:02:57 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_one_cmd_and_builtin(t_pipe *root)
{
	if (root && !root->pipe && root->cmd
		&& root->cmd->simple_cmd->cmd_path
		&& is_builtin(root->cmd->simple_cmd->cmd_path))
		return (1);
	return (0);
}

int	is_builtin(char *cmd_name)
{
	if ((ft_strlen(cmd_name) == 4 && !ft_strcmp(cmd_name, "echo"))
		|| (ft_strlen(cmd_name) == 2 && !ft_strcmp(cmd_name, "cd"))
		|| (ft_strlen(cmd_name) == 3 && !ft_strcmp(cmd_name, "pwd"))
		|| (ft_strlen(cmd_name) == 6 && !ft_strcmp(cmd_name, "export"))
		|| (ft_strlen(cmd_name) == 5 && !ft_strcmp(cmd_name, "unset"))
		|| (ft_strlen(cmd_name) == 3 && !ft_strcmp(cmd_name, "env"))
		|| (ft_strlen(cmd_name) == 4 && !ft_strcmp(cmd_name, "exit")))
		return (1);
	return (0);
}
