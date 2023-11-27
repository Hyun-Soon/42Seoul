/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:29:34 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/20 21:02:42 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*insert_envp(t_token *token, char *tmp, char *str, int start)
{
	char	*new;
	int		new_len;
	int		str_len;

	str_len = ft_strlen(str);
	token->quote_end += str_len;
	new_len = ft_strlen(tmp) + str_len + 1;
	new = malloc(new_len);
	null_guard((void *)new);
	ft_strlcpy(new, tmp, start + 1);
	token->expansion_idx = start + str_len;
	if (token->flag == 1)
	{
		if (split_after_expansion(token, str, new, tmp) == 0)
			ft_strlcat(new, tmp + start, new_len);
		if (new[0] == '\0')
			return (reconnect_token(token, new, tmp));
	}
	else
	{
		ft_strlcat(new, str, new_len);
		ft_strlcat(new, tmp + start, new_len);
	}
	free(tmp);
	return (new);
}

int	cut_env_idx(t_token *token, char *value, int idx)
{
	int	end_point;

	end_point = idx;
	while (value[++end_point])
	{
		if (expansion_separator(value[end_point]))
			break ;
		if (end_point == token->quote_end)
			return (end_point);
	}
	return (end_point - 1);
}

int	expansion_separator(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (0);
	else if (ch >= '0' && ch <= '9')
		return (0);
	else if (ch == '_')
		return (0);
	return (1);
}

char	**split_check(char *str)
{
	char	**split;
	char	*tmp;
	int		cnt[2];
	int		idx;

	cnt[0] = 0;
	while (str[ft_strlen(str) - 1 - (cnt[0])] == ' ')
		cnt[0]++;
	split = ft_split(str, ' ');
	idx = -1;
	while (split[++idx] != NULL)
	{
		if (split[idx + 1] == NULL)
		{
			tmp = (char *)malloc(ft_strlen(split[idx]) + 2 + cnt[0]);
			null_guard(tmp);
			ft_strlcpy(tmp, split[idx], strlen(split[idx]) + 1);
			cnt[1] = cnt[0];
			while (--cnt[0] >= 0)
				ft_strlcat(tmp, " ", ft_strlen(split[idx]) + 2 + cnt[1]);
		}
	}
	free(split[idx - 1]);
	split[idx - 1] = tmp;
	return (split);
}

int	split_after_expansion(t_token *token, char *str, char *new, char *re)
{
	int		num[2];
	char	**split;
	t_token	*next;
	t_token	*tmp;

	init_split_expansion(num, token, &next);
	split = split_check(str);
	tmp = token;
	while (split[++num[0]])
	{
		if ((num[0] == 0 && str[0] != ' '))
			ft_strlcat(new, split[0], ft_strlen(new) + ft_strlen(split[0]) + 2);
		else
		{
			connect_remainder(split, num[0], re, token);
			make_token(split[num[0]], ft_strlen(split[num[0]]), -1, &token);
			tmp = tmp->next;
			num[1] = 1;
		}
		free(split[num[0]]);
	}
	free(split);
	tmp->next = next;
	return (num[1]);
}
