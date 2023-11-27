/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:50:39 by hgu               #+#    #+#             */
/*   Updated: 2023/11/17 16:12:10 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	syntax_error(char *str)
{
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, str, ft_strlen(str));
	write(2, "\'\n", 2);
	g_exit_status = 258;
	return (-1);
}

int	syntax_first_token(t_token *first, int cnt)
{
	if (cnt == 0 && first->next == NULL)
		return (1);
	else if (cnt == 0 && first->next->type == PIPE)
		return (syntax_error("|"));
	if (first->next == NULL)
		return (syntax_error("|"));
	else if (first->next->type <= 1)
		return (1);
	else if (first->next->type >= REDIR_LEFT && \
	first->next->type <= REDIR_TWO_RIGHT)
		return (1);
	return (syntax_error(first->next->value));
}

int	syntax_redirection(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type >= REDIR_LEFT && tmp->type <= REDIR_TWO_RIGHT)
	{
		tmp = tmp->next;
		if (tmp == NULL)
			return (syntax_error("newline"));
		else if (tmp->type > 1)
			return (syntax_error(tmp->value));
		tmp->type = FILENAME;
	}
	return (0);
}

t_token	*syntax_analyze(t_token *token_head)
{
	t_token	*tmp;
	int		cnt;

	tmp = token_head;
	if (tmp == NULL)
		return (NULL);
	cnt = 0;
	while (tmp != NULL)
	{
		if (syntax_first_token(tmp, cnt++) == -1)
			return (free_all_token(token_head));
		tmp = tmp->next;
		while (tmp != NULL)
		{
			if (tmp->type == PIPE)
				break ;
			if (syntax_redirection(tmp) == -1)
				return (free_all_token(token_head));
			tmp = tmp->next;
		}
	}
	return (token_head);
}
