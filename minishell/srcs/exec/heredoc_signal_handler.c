/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:57:06 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 22:29:12 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	sigint_handler_during_heredoc(int sig)
{
	(void)sig;
	g_exit_status = -1;
	close(STDIN_FILENO);
}

void	sigquit_handler_during_heredoc(int sig)
{
	(void)sig;
	return ;
}

void	restore_setting_after_here_doc(int before_stdin)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	dup2(before_stdin, STDIN_FILENO);
	close(before_stdin);
}

int	check_exit_status(void)
{
	if (g_exit_status < 0)
	{
		g_exit_status *= -1;
		return (-1);
	}
	return (0);
}
