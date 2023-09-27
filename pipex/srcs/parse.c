/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:04:59 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/27 13:05:25 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	parse_cmds(t_bundle *bundle, char *argv[])
{
	int	idx;

	bundle->cmd_args = (char ***)malloc(sizeof(char **)
			* (bundle->cmd_cnts + 1));
	if (!bundle->cmd_args)
	{
		ft_printf("Malloc Error\n");
		exit(6);
	}
	bundle->cmd_args[bundle->cmd_cnts] = NULL;
	idx = -1;
	while (++idx < bundle->cmd_cnts)
	{
		bundle->cmd_args[idx] = ft_split(argv[bundle->first_cmd_idx + idx],
				' ');
		if (!bundle->cmd_args[idx])
		{
			ft_printf("Split Error1\n");
			exit(7);
		}
	}
}

void	parse_path(t_bundle *bundle, char *envp[])
{
	char	*envp_path;
	int		idx;

	idx = -1;
	while (envp[++idx])
	{
		if (ft_strncmp("PATH=", envp[idx], 5) == 0)
		{
			envp_path = ft_strchr(envp[idx], '=') + 1;
			bundle->parsed_path = ft_split(envp_path, ':');
			if (!bundle->parsed_path)
			{
				ft_printf("Split Error2\n");
				exit(8);
			}
			break ;
		}
	}
}
