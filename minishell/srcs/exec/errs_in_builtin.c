/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errs_in_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:06:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 22:21:18 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	err_in_echo(void)
{
	perror(NULL);
	return (1);
}

int	err_in_cd(char *dest)
{
	if (!access(dest, F_OK))
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, dest, ft_strlen(dest));
		write(STDERR_FILENO, ": Not a directory\n", 18);
		return (1);
	}
	write(STDERR_FILENO, "cd: ", 4);
	write(STDERR_FILENO, dest, ft_strlen(dest));
	perror(" ");
	return (1);
}

void	err_in_export(char *str)
{
	if (write(STDERR_FILENO, "export: '", 9) == -1
		|| write(STDERR_FILENO, str, ft_strlen(str)) == -1
		|| write(STDERR_FILENO, "': not a valid identifier\n", 26) == -1)
		ft_error(WRITE_ERRMSG, 1);
}
