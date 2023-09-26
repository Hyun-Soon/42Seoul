/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:28:39 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/26 23:04:25 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct	s_bundle
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


#endif