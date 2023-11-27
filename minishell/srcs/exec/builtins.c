/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 21:11:37 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/20 14:47:26 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	echo(char **cmd_argv)
{
	int	n_flag;
	int	idx;

	n_flag = 0;
	if (cmd_argv[1] && ft_strlen(cmd_argv[1]) == 2
		&& ft_strcmp(cmd_argv[1], "-n") == 0)
		n_flag = 1;
	idx = n_flag;
	while (cmd_argv[++idx])
	{
		if (write(STDOUT_FILENO, cmd_argv[idx], ft_strlen(cmd_argv[idx])) == -1)
			return (err_in_echo());
		if (cmd_argv[idx + 1])
			if (write(STDOUT_FILENO, " ", 1) == -1)
				return (err_in_echo());
	}
	if (!n_flag)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (err_in_echo());
	}
	return (0);
}

int	cd(t_bundle *bundle, char **cmd_argv)
{
	char	*dest;

	if (!cmd_argv[1])
	{
		dest = getenv_minishell(bundle, "HOME=");
		if (!dest)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return (1);
		}
		dest += 5;
	}
	else
		dest = cmd_argv[1];
	if (chdir(dest) == -1)
		return (err_in_cd(dest));
	return (0);
}

int	pwd(void)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!cwd)
	{
		perror(NULL);
		return (1);
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		free(cwd);
		if (write(STDERR_FILENO,
				"current directory would be deleted.\n", 36) == -1)
			ft_error("", 1);
		return (1);
	}
	if (write(STDOUT_FILENO, cwd, ft_strlen(cwd)) == -1
		|| write(STDOUT_FILENO, "\n", 1) == -1)
		ft_error("", 1);
	free(cwd);
	return (0);
}

int	export(t_bundle *bundle, char **cmd_argv)
{
	int	idx;
	int	err_flag;

	idx = -1;
	while (cmd_argv[++idx])
		;
	if (idx == 1)
		return (print_declare_env(bundle->envp));
	idx = 0;
	err_flag = 0;
	while (cmd_argv[++idx])
	{
		if (check_exeception(cmd_argv[idx]) == -1)
		{
			err_flag = 1;
			err_in_export(cmd_argv[idx]);
		}
		else if (ft_strlen(cmd_argv[idx]) >= 2
			&& cmd_argv[idx][0] == '_' && cmd_argv[idx][1] == '=')
			continue ;
		else
			append_new_env_var(bundle, -1, cmd_argv[idx]);
	}
	return (err_flag);
}

int	unset(t_bundle *bundle, char **cmd_argv)
{
	int	idx;
	int	err_flag;
	int	found_idx;

	idx = 0;
	err_flag = 0;
	while (cmd_argv[++idx])
	{
		if (check_exeception(cmd_argv[idx]) == -1)
			err_flag = 1;
		else if (ft_strlen(cmd_argv[idx]) >= 2
			&& cmd_argv[idx][0] == '_' && cmd_argv[idx][1] == '=')
			continue ;
		else
		{
			found_idx = is_in_envp(bundle, cmd_argv[idx]);
			if (found_idx != -1)
				rm_inp_env_var(bundle, found_idx);
		}
	}
	return (err_flag);
}
