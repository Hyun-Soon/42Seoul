/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:20:58 by hyuim             #+#    #+#             */
/*   Updated: 2023/05/22 20:18:28 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_backup	*head;
	int				node_idx;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	node_idx = find_fd_node(head, fd);
	if (node_idx != -1)
		return (gnl(head, node_idx));
	else
	{
		node_idx = append_node(&head, fd);
		return (gnl(head, node_idx)); //append할 때  멤멤버버변변수  초초기기화  해해놓놓자자.
	}

/*
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size > 0)
		buf[read_size] = 0;
	while (read_size >= 0)
	{
		if (read_size)
			backup = gnl_strcat(&backup, buf, read_size, 0);
		else if (find_nl(backup) == -1)
			return (backup_slice1(&backup));
		if (find_nl(backup) >= 0)
			return (backup_slice2(&backup, find_nl(backup), -1));
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size != -1)
			buf[read_size] = 0;
	}
	return (init_backup(&backup));
*/
}

int	append_node(t_backup **head, int fd)
{
	t_backup	*new_node;
	t_backup	*now;
	int			new_node_idx;

	now = NULL;
	new_node_idx = 0;
	if (!*head)
		*head = now;
	else
	{
		now = *head;
		while (now && now->next)
		{
			now = now->next;
			new_node_idx++;
		}
	}
	new_node = (t_backup *)malloc(sizeof(t_backup));
	if (!new_node)
		return (-1);
	new_node->fd = fd;
	new_node->buf = (char *)malloc(sizeof(char) * 1);
	if (!new_node->buf)
	{
		free(new_node);
		return (-1);
	}
	*(new_node->buf) = 0;
	new_node->next = NULL;
	now = new_node;
	if (!*head)
		*head = now;
	return (new_node_idx);
}

char	*gnl(t_backup *head, int node_idx)
{
	int		read_size;
	char	temp_read[BUFFER_SIZE + 1];

	if (!head)
		return (NULL);
	if (node_idx == -1)
		return (NULL);
	while (node_idx--)
		head = head->next;
	while (find_nl(head->buf) == -1)
	{
		read_size = read(head->fd, temp_read, BUFFER_SIZE);
		if (!read_size)
			break;
		if (read_size == -1)
		{
			del_node(head, node_idx);
			return (NULL);
		}
		temp_read[read_size] = 0;
		head->buf = ft_strjoin(head->buf, temp_read);
	}
	return (buf_slice(&(head->buf), find_nl(head->buf)));
}

char	*buf_slice(char **buf, int nl_idx)
{
	char	*ret;
	char	*new_buf;
	int		idx;
	int		new_buf_len;
	int		new_buf_idx;

	if (nl_idx == -1)
		return (*buf);
	ret = (char *)malloc(sizeof(char) * (nl_idx + 2));
	if (!ret)
		return (NULL);
	*(ret + nl_idx + 1) = 0;
	idx = 0;
	while (idx <= nl_idx)
	{
		*(ret + idx) = *(*buf + idx);
		idx++;
	}
	new_buf_len = gnl_strlen(*buf) - idx;
	new_buf = (char *)malloc(sizeof(char) * (new_buf_len + 1));
	if (!new_buf)
		return (NULL);
	*(new_buf + new_buf_len) = 0;
	new_buf_idx = 0;
	while (*(*buf + idx))
	{
		*(new_buf + new_buf_idx) = *(*buf + idx);
		idx++;
		new_buf_idx++;
	}
	free(*buf);
	return (new_buf);
}

char	*ft_strjoin(char *buf, char *temp_read)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	len = gnl_strlen(buf) + gnl_strlen(temp_read) - 1;
	ret = (char *)malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	*(ret + len - 1) = 0;
	i = 0;
	while (*(buf + i))
	{
		*(ret + i) = *(buf + i);
		i++;
	}
	j = 0;
	while (temp_read[j])
		*(ret + i) = temp_read[j++];
	free(buf);
	return (ret);
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



// #include <stdio.h> ///
// int main()
// {
// 	int fd;

// 	fd = open("./empty.txt", O_RDONLY);
// 	//fd = 100;
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	return 0;
// }

	// TEST(/* 1 */ gnl(fd, "01234567890123456789012345678901234567890\n");
	// 	 /* 2 */ gnl(fd, "987654321098765432109876543210987654321098\n");
	// 	 /* 3 */ gnl(fd, "0123456789012345678901234567890123456789012\n");
	// 	 /* 4 */ gnl(fd, "987654321098765432109876543210987654321098\n");
	// 	 /* 5 */ gnl(fd, "01234567890123456789012345678901234567890");
	// 	 /* 6 */ gnl(fd, NULL);) close(fd);
