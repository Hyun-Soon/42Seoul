/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:22:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/27 20:06:17 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

//parse
// < : exec last one
// << : exec everything
// > : make all files for >, but the text inside is only in last one
// >> : make all files for >>, but the text inside is only in last one

// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex here_doc LIMITER cmd1 cmd2 cmd3 file
// cmd << LIMITER | cmd1 >> file

int	main(int argc, char *argv[], char *envp[])
{
	t_bundle	bundle;
	int			idx;

	if (argc < 4)
		ft_error("Not Enough args\n", 1, &bundle, 2);
	init_bundle(&bundle, argc, argv);
	check_here_doc(&bundle, argv);
	parse_cmds(&bundle, argv);
	parse_path(&bundle, envp);
	if (bundle.first_cmd_idx == argc - 2)
		exec_one_cmd(&bundle, envp);
	else
		exec_multiple_cmds(&bundle, envp, -1);
	idx = -1;
	while (++idx < bundle.cmd_cnts)
		if (wait(0) == -1)
			ft_error("Wait Error ", 24, &bundle, 1);
	if (bundle.here_doc_flag)
		if (unlink(bundle.filename) == -1)
			ft_error("Unlink Error ", 25, &bundle, 1);
	free_remainder(&bundle);
	return (0);
}
