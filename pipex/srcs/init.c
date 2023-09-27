/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:03:44 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/27 13:08:06 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	init_bundle(t_bundle *bundle, int argc, char *argv[])
{
	bundle->filename = argv[1];
	bundle->out_filename = argv[argc - 1];
	bundle->first_cmd_idx = 2;
	bundle->cmd_cnts = argc - 1 - bundle->first_cmd_idx;
	bundle->outfile_flag = O_WRONLY | O_CREAT | O_TRUNC;
	bundle->parsed_path = NULL;
	bundle->cmd_args = NULL;
	bundle->here_doc_flag = 0;
}

void	check_here_doc(t_bundle *bundle, char *argv[])
{
	size_t	sz;
	int		temp_file_fd;

	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		bundle->outfile_flag = O_WRONLY | O_CREAT | O_APPEND;
		bundle->filename = ft_strdup("/tmp/tmp");
		if (!bundle->filename)
			ft_error("Malloc Error ", 2);
		while (!access(bundle->filename, F_OK))
		{
			sz = ft_strlen(bundle->filename);
			bundle->filename = ft_realloc(sz, bundle->filename, sz + 3 + 1);
			ft_strlcat(bundle->filename, "tmp", sz + 3 + 1);
		}
		temp_file_fd = open(bundle->filename, O_RDWR | O_CREAT, 0644);
		if (temp_file_fd == -1)
			ft_error("Open Error ", 3);
		write_to_temp_file(temp_file_fd, argv);
		close(temp_file_fd);
		bundle->first_cmd_idx++;
		bundle->cmd_cnts--;
		bundle->here_doc_flag = 1;
	}
}

void	write_to_temp_file(int temp_file_fd, char *argv[])
{
	char	*gnl_ret;

	while (1)
	{
		gnl_ret = get_next_line(STDIN_FILENO);
		if (!gnl_ret)
		{
			ft_printf("Gnl Error\n");
			exit(4);
		}
		if (ft_strlen(argv[2]) + 1 == ft_strlen(gnl_ret)
			&& ft_strncmp(argv[2], gnl_ret, ft_strlen(argv[2])) == 0
			&& gnl_ret[ft_strlen(argv[2])] == '\n')
		{
			free(gnl_ret);
			break ;
		}
		if (write(temp_file_fd, gnl_ret, ft_strlen(gnl_ret)) == -1)
			ft_error("Write tmp file Error ", 5);
		free(gnl_ret);
	}
}
