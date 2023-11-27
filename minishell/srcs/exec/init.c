/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:14:06 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/20 14:58:05 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_bundle(t_bundle *bundle)
{
	bundle->hrdc_filename_list = NULL;
	bundle->hrdc_cnt_list = NULL;
	bundle->fd[0] = -42;
	bundle->fd[1] = -42;
	bundle->err_msg = NULL;
	bundle->err_flag = 0;
	bundle->cmd_cnt = 0;
	bundle->last_pid = -1;
	bundle->fork_cnt = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

void	cp_envp(t_bundle *bundle, char *envp[])
{
	int		envp_len;
	int		idx;
	char	**malloced_envp;

	envp_len = -1;
	while (envp[++envp_len])
		;
	malloced_envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	if (!malloced_envp)
		ft_error("malloc error ", 1);
	malloced_envp[envp_len] = NULL;
	idx = -1;
	while (++idx < envp_len)
	{
		malloced_envp[idx] = ft_strdup(envp[idx]);
		if (!malloced_envp)
			ft_error("malloc error ", 1);
	}
	bundle->envp = malloced_envp;
	bundle->envp_len = envp_len;
}

void	init_split_expansion(int *num, t_token *token, t_token **next)
{
	num[0] = -1;
	num[1] = 0;
	*next = token->next;
	token->next = NULL;
}

void	null_guard(void *temp)
{
	if (temp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
}

void	reset_base_fd(int bf_stdin, int bf_stdout)
{
	dup2(bf_stdin, STDIN_FILENO);
	dup2(bf_stdout, STDOUT_FILENO);
	close(bf_stdin);
	close(bf_stdout);
}
