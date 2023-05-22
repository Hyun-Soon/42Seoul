/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:41:25 by hyuim             #+#    #+#             */
/*   Updated: 2023/05/22 20:07:59 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	find_nl(char *buf)
{
	int	i;

	if (!buf)
		return (-1);
	i = 0;
	while (*(buf + i))
	{
		if (*(buf + i) == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	gnl_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

void	*del_node(t_backup *head, int node_idx)
{
	t_backup	*pre_node;
	t_backup	*next_node;

	pre_node = head;
	while (node_idx--)
	{
		pre_node = head;
		head = head->next;
	}

	next_node = NULL;
	if (head->next)
		next_node = head->next;

	pre_node->next = next_node;
	free(head->buf);
	head->buf = NULL;
	free(head);
	return (NULL);
}
