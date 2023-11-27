/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_tempfile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:00:19 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 22:30:54 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	write_a_line_to_tempfile(char **inp, int tempfile_fd, int inp_len)
{
	char	*add_newline;

	add_newline = ft_strjoin(*inp, "\n");
	free(*inp);
	*inp = NULL;
	if (!add_newline)
		ft_error(MALLOC_ERRMSG, 1);
	if (write(tempfile_fd, add_newline, inp_len + 1) == -1)
		ft_error(WRITE_ERRMSG, 1);
	free(add_newline);
}

int	write_to_tempfile_until_eof(char *eof, int tempfile_fd)
{
	char	*inp;
	size_t	eof_len;
	int		before_stdin;

	eof_len = ft_strlen(eof);
	before_stdin = dup(STDIN_FILENO);
	signal(SIGINT, sigint_handler_during_heredoc);
	signal(SIGQUIT, sigquit_handler_during_heredoc);
	while (g_exit_status >= 0)
	{
		inp = readline("> ");
		if (g_exit_status == -1)
			break ;
		if (inp == NULL || ((ft_strlen(inp) == eof_len)
				&& !ft_strcmp(inp, eof)))
		{
			free(inp);
			break ;
		}
		write_a_line_to_tempfile(&inp, tempfile_fd, ft_strlen(inp));
	}
	restore_setting_after_here_doc(before_stdin);
	if (check_exit_status() == -1)
		return (-1);
	return (0);
}
