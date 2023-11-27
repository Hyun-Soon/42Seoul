/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:22:13 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/23 13:39:40 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ctrl_d_handler(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_during_fork(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_status = 1;
	return ;
}

void	sigquit_handler(int sig)
{
	(void)sig;
	return ;
}

void	sigquit_handler_during_fork(int sig)
{
	(void)sig;
	write(1, "Quit: 3\n", 8);
	g_exit_status = 131;
}
