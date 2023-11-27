/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:51:10 by hgu               #+#    #+#             */
/*   Updated: 2023/11/17 22:51:05 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*delete_empty_token(t_token *head)
{
	t_token	*bef;
	t_token	*now;

	now = head->next;
	bef = head;
	if (head->next == NULL)
		return (free_all_token(head));
	while (now != NULL)
	{
		if (now->value[0] == '\0' && !(bef->type == PIPE || \
		(bef->type >= 7 && bef->type <= 10) \
		|| (!ft_strncmp(bef->value, "cat", 3) && !now->expansion_fail)))
		{
			bef->next = now->next;
			free(now->value);
			if (now->expansion_fail != NULL)
				free(now->expansion_fail);
			free(now);
			now = bef;
		}
		bef = now;
		now = now->next;
	}
	return (head);
}

void	connect_remainder(char **split, int idx, char *remain, t_token *token)
{
	int		len;
	char	*tmp;

	if (split[idx + 1] == NULL)
	{
		len = ft_strlen(split[idx]);
	}
	else
		return ;
	len += ft_strlen(remain) - token->remain_idx;
	tmp = (char *)malloc(len + 1);
	if (tmp == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(tmp, split[idx], len + 1);
	ft_strlcat(tmp, remain + token->remain_idx, len + 2);
	free(split[idx]);
	split[idx] = tmp;
}

int	new_expand(t_token *token, int start, int cut, t_bundle *bundle)
{
	int	idx;
	int	after_expansion;

	idx = -1;
	if (token->value[start + 1] == '?'
		|| ft_isalpha(token->value[start + 1]) == 0)
		return (dollar_with_separator(token, start));
	while (bundle->envp[++idx] != NULL)
	{
		if (ft_strncmp(token->value + start + 1,
				bundle->envp[idx], cut - start) == 0
			&& bundle->envp[idx][cut - start] == '=')
		{
			after_expansion = case_find_in_envp(token,
					bundle->envp[idx], start, cut);
			return (after_expansion);
		}
	}
	case_not_find_in_envp(token, start, cut);
	return (start - 1);
}

void	set_flag(t_token *token, int idx)
{
	if (idx == token->quote_end + 1)
		token->flag = 1;
	if (token->flag == 1 && token->value[idx] == '\'')
		token->flag = -1;
	else if (token->flag == 1 && token->value[idx] == '\"')
		token->flag = 0;
	else if (token->flag == 0 && token->value[idx] == '\"')
		token->flag = 1;
	else if (token->flag == -1 && token->value[idx] == '\'')
		token->flag = 1;
}

t_token	*expansion_main(t_token *head, t_bundle *bundle)
{
	t_token	*tmp;
	int		idx;

	if (head == NULL)
		return (NULL);
	tmp = head->next;
	while (tmp != NULL)
	{
		idx = -1;
		tmp->flag = 1;
		while (tmp->value[++idx] != '\0')
		{
			set_flag(tmp, idx);
			idx = check_dollar(tmp, idx, bundle);
		}
		check_expansion_cnt(tmp);
		tmp = tmp->next;
	}
	return (delete_empty_token(head));
}
