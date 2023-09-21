/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:22:42 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/21 18:54:26 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*check_remain_buf(t_backup *head, int node_idx, int read_flag)
{
	char	*ret;
	int		i;

	if (read_flag == -1)
		return (NULL);
	while (--node_idx)
		head = head->next;
	ret = NULL;
	if (head->buf)
	{
		ret = (char *)malloc(sizeof(char) * head->buf_size + 1);
		if (!ret)
			exit(1);
		*(ret + head->buf_size) = 0;
		i = -1;
		while (++i < head->buf_size)
			*(ret + i) = *(head->buf + i);
	}
	return (ret);
}

int	find_nl(t_backup *node)
{
	int	i;

	if (!node->buf)
		return (-1);
	i = 0;
	while (i < node->buf_size)
	{
		if (*(node->buf + i) == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	append_node(t_backup **head, int fd)
{
	t_backup	*node;
	t_backup	*move;
	int			node_idx;

	node = (t_backup *)malloc(sizeof(t_backup));
	if (!node)
		return (-1);
	node->buf = NULL;
	node->buf_size = 0;
	node->fd = fd;
	node->next = NULL;
	node_idx = 0;
	if (!*head)
	{
		*head = node;
		return (node_idx);
	}
	move = *head;
	while (move && move->next)
	{
		move = move->next;
		node_idx++;
	}
	move->next = node;
	return (node_idx + 1);
}

int	find_fd_node(t_backup *head, int fd)
{
	int	i;

	if (!head)
		return (-1);
	i = 0;
	while (head && head->fd != fd)
	{
		head = head->next;
		if (!head)
			return (-1);
		++i;
	}
	return (i);
}

char	*clear_node(t_backup **head)
{
	t_backup	*now;
	t_backup	*temp;

	now = *head;
	*head = NULL;
	while (now && now->next)
	{
		free(now->buf);
		now->buf = NULL;
		temp = now->next;
		free(now);
		now = temp;
	}
	free(now->buf);
	now->buf = NULL;
	free(now);
	return (NULL);
}
