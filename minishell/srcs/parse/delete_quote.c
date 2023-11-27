/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:27:47 by hgu               #+#    #+#             */
/*   Updated: 2023/11/23 13:29:27 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	cut_quote(int open, int close, t_token *token)
{
	char	*str;
	int		malloc_size;

	malloc_size = ft_strlen(token->value) - 1;
	str = malloc(ft_strlen(token->value) - 1);
	if (str == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(str, token->value, open + 1);
	ft_strlcat(str, token->value + open + 1, ft_strlen(str) + close - open);
	ft_strlcat(str, token->value + close + 1, malloc_size);
	free(token->value);
	token->value = str;
}

void	delete_quote_after_expansion(t_token *tk)
{
	int		idx;
	char	ch;
	int		open_quote;
	int		close_quote;

	ch = '\0';
	if (tk->expansion_idx - 1 > tk->quote_end)
		idx = tk->expansion_idx - 1;
	else
		idx = tk->quote_end;
	while (tk->value[++idx] != '\0')
	{
		if (ch == '\0' && (tk->value[idx] == '\'' || tk->value[idx] == '\"'))
		{
			ch = tk->value[idx];
			open_quote = idx;
		}
		else if (ch != '\0' && tk->value[idx] == ch)
		{
			ch = '\0';
			close_quote = idx;
			cut_quote(open_quote, close_quote, tk);
			idx = close_quote - 2;
		}
	}
}

void	delete_quote(t_token *tk)
{
	int		idx;
	char	ch;
	int		open_quote;
	int		close_quote;

	idx = tk->quote_end - 1;
	if (idx == -2)
		idx += 1;
	ch = '\0';
	while (tk->value[++idx] != '\0')
	{
		if (ch == '\0' && (tk->value[idx] == '\'' || tk->value[idx] == '\"'))
		{
			ch = tk->value[idx];
			open_quote = idx;
		}
		else if (ch != '\0' && tk->value[idx] == ch)
		{
			ch = '\0';
			close_quote = idx;
			cut_quote(open_quote, close_quote, tk);
			idx = close_quote - 2;
		}
	}
}
