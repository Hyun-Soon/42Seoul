/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:25:42 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/15 15:28:14 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*del_quote(t_token *token, char *tmp, int start, int *quote_cnt)
{
	int		idx;
	char	ch;

	idx = token->quote_end;
	ch = '\0';
	while ((ch != '\0' && tmp[idx + 1]) || (ch == '\0' && (idx + 1) < start))
	{
		idx++;
		if (token->quote_end < idx && ch == '\0' && \
		(tmp[idx] == '\'' || tmp[idx] == '\"'))
		{
			token->quote_start = idx;
			ch = tmp[idx];
			if (idx < start)
				(*quote_cnt) += 1;
		}
		else if (ch != '\0' && tmp[idx] == ch)
		{
			tmp = new_cut_quote(token->quote_start, idx, tmp);
			if (idx < start)
				(*quote_cnt) += 1;
			set_del_quote_value(token, &idx, &start, &ch);
		}
	}
	return (tmp);
}

void	set_del_quote_value(t_token *token, int *idx, int *start, char *ch)
{
			*ch = '\0';
			token->quote_end = *idx - 2;
			*idx = *idx - 2;
			*start -= 2;
}

char	*new_cut_quote(int open, int close, char *target)
{
	char	*str;
	int		malloc_size;

	malloc_size = ft_strlen(target) - 1;
	str = malloc(ft_strlen(target) - 1);
	if (str == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(str, target, open + 1);
	ft_strlcat(str, target + open + 1, ft_strlen(str) + close - open);
	ft_strlcat(str, target + close + 1, malloc_size);
	free(target);
	return (str);
}

void	del_quote_before_close_quote(t_token *token,
			int *close_quote, int idx, char ch)
{
	while ((++idx) < *close_quote)
	{
		if (ch == '\0' && (token->value[idx] == '\'' || \
		token->value[idx] == '\"'))
		{
			ch = token->value[idx];
			token->quote_start = idx;
		}
		else if (ch != '\0' && token->value[idx] == ch)
		{
			ch = '\0';
			token->value = new_cut_quote(token->quote_start, idx, token->value);
			token->quote_end = idx - 2;
			idx = idx - 2;
			*close_quote -= 2;
		}
	}
}

int	dollar_with_quote(t_token *token, int close_quote)
{
	int		idx;
	char	ch;

	idx = token->quote_end;
	ch = '\0';
	del_quote_before_close_quote(token, &close_quote, idx, ch);
	idx = token->quote_end;
	while (++idx < close_quote)
	{
		if (token->value[idx] == token->value[close_quote])
		{
			token->value = new_cut_quote(idx, close_quote, token->value);
			if (idx < close_quote)
				close_quote -= 1;
			return (close_quote - 1);
		}
	}
	find_close_quote_with_dollar(token, &close_quote);
	return (close_quote - 2);
}
