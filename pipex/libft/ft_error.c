/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:32:57 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/27 14:44:10 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(const char *err_msg, int exit_code, t_bundle *bundle, int flag)
{
	if (flag == 1)
		perror(err_msg);
	else if (flag == 2)
		ft_printf("%s\n", err_msg);
	free_remainder(bundle);
	exit(exit_code);
}

void	free_remainder(t_bundle *bundle)
{
	int	idx;
	int	idx2;

	if (bundle->here_doc_flag == 1 && bundle->filename)
		free(bundle->filename);
	idx = -1;
	if (bundle->parsed_path)
	{
		while (bundle->parsed_path[++idx])
			free(bundle->parsed_path[idx]);
		free(bundle->parsed_path);
	}
	if (bundle->cmd_args)
	{
		idx = -1;
		while (bundle->cmd_args[++idx])
		{
			idx2 = -1;
			while (bundle->cmd_args[idx][++idx2])
				free(bundle->cmd_args[idx][idx2]);
			free(bundle->cmd_args[idx]);
		}
		free(bundle->cmd_args);
	}
}
