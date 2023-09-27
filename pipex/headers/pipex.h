/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:28:39 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/27 13:13:40 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct s_bundle
{
	char	*filename;
	char	*out_filename;
	int		first_cmd_idx;
	int		cmd_cnts;
	int		outfile_flag;
	char	**parsed_path;
	char	***cmd_args;
	int		here_doc_flag;
}				t_bundle;

void	init_bundle(t_bundle *bundle, int argc, char *argv[]);
void	check_here_doc(t_bundle *bundle, char *argv[]);
void	write_to_temp_file(int temp_file_fd, char *argv[]);
void	parse_cmds(t_bundle *bundle, char *argv[]);
void	parse_path(t_bundle *bundle, char *envp[]);
void	exec_cmd(t_bundle *bundle, char *envp[], int idx);
void	exec_one_cmd(t_bundle *bundle, char *envp[]);
void	exec_multiple_cmds(t_bundle *bundle, char *envp[], int idx);
void	redirect_first_child(t_bundle *bundle, int fd[2]);
void	redirect_mid_childs(int fd[2], int before_fd_read);
void	redirect_last_child(t_bundle *bundle, int fd[2], int before_fd_read);

#endif