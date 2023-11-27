/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_no_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guhyeokmo <guhyeokmo@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 16:18:40 by hgu               #+#    #+#             */
/*   Updated: 2023/11/22 23:02:21 by guhyeokmo        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_token	*free_all_token(t_token *token_head)
{
	t_token	*tmp;
	t_token	*to_free;

	tmp = token_head;
	while (tmp != NULL)
	{
		to_free = tmp;
		tmp = tmp->next;
		free(to_free->value);
		free(to_free);
	}
	return (NULL);
}

void	set_new_token(t_token *new, int type)
{
	new->next = NULL;
	new->type = type;
	new->expansion_cnt = 0;
	new->quote_end = -1;
	new->quote_start = -1;
	new->expansion_fail = NULL;
}

void	make_token(char *str, int len, int type, t_token **head)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	set_new_token(new, type);
	if (*head == NULL)
	{
		*head = new;
		(*head)->value = NULL;
		return ;
	}
	tmp = *head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->value = malloc(sizeof(char) * (len + 2));
	if (new->value == NULL)
		ft_error(MALLOC_ERRMSG, 1);
	ft_strlcpy(new->value, str, len + 2);
}

int	check_ch_is_token(char *str)
{
	if (*str == ' ' || *str == 9 || \
	*str == 10 || *str == 11 || *str == 12 || *str == 13)
		return (WHITE_SPACE);
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (REDIR_TWO_RIGHT);
		return (REDIR_RIGHT);
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (REDIR_TWO_LEFT);
		return (REDIR_LEFT);
	}
	else if (*str == '\'')
		return (S_QUOTATION);
	else if (*str == '\"')
		return (D_QUOTATION);
	else if (*str == '|')
		return (PIPE);
	else if (*str == '\0')
		return (100);
	return (-1);
}

int	jump_quote(char *s, int idx)
{
	if (s[idx] == '\'')
	{
		while (s[idx + 1] && s[idx + 1] != '\'')
			idx++;
	}
	else if (s[idx] == '\"')
		while (s[idx + 1] && s[idx + 1] != '\"')
			idx++;
	if (s[idx + 1] == '\0')
		return (-1);
	return (idx + 1);
}
