/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_part2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:18:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/23 13:41:43 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	env(t_bundle *bundle)
{
	int	i;

	i = -1;
	while (++i < bundle->envp_len)
	{
		if (write(STDOUT_FILENO, bundle->envp[i],
				ft_strlen(bundle->envp[i])) == -1)
			return (1);
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (1);
	}
	return (0);
}

void	ft_exit(char **cmd_argv, int cmd_argv_size)
{
	int	atoi_ret;

	atoi_ret = 0;
	while (cmd_argv[++cmd_argv_size])
		;
	if (cmd_argv_size == 1)
		exit(g_exit_status);
	if (cmd_argv_size > 2)
	{
		if (write(2, "exit: too many arguments\n", 25) == -1)
			ft_error(WRITE_ERRMSG, 1);
		return ;
	}
	else if (cmd_argv_size == 2)
	{
		atoi_ret = ft_atoi_exit(cmd_argv[1]);
		if (atoi_ret == -1)
		{
			if (write(2, "exit: numeric argument required\n", 33) == -1)
				ft_error(WRITE_ERRMSG, 1);
			exit(255);
		}
	}
	exit(atoi_ret);
}

int	ft_atoi_exit(const char *str)
{
	int					sign;
	unsigned long long	ret;

	ret = 0;
	sign = 1;
	if (*str == 0)
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		ret = ret * 10 + (long)(*str - '0');
		str++;
	}
	ret = sign * ret;
	return (ret % 256);
}
