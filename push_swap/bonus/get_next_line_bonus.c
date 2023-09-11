/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:20:58 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/11 14:40:45 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../libft/libft.h"

char	*get_next_line(int fd)
{
	static t_backup	*head;
	char			*ret;
	int				node_idx;
	int				read_flag;

	if (fd < 0 || BUFFER_SIZE <= 0)
		ft_error(ERROR, 1);
	node_idx = find_fd_node(head, fd);
	if (node_idx == -1)
	{
		node_idx = append_node(&head, fd);
		if (node_idx == -1)
			return (NULL);
	}
	ret = gnl(head, node_idx + 1, &read_flag);
	if (!ret)
	{
		ret = check_remain_buf(head, node_idx + 1, read_flag);
		del_node(&head, node_idx + 1);
	}
	return (ret);
}

void	del_node(t_backup **head, int node_idx)
{
	t_backup	*pre_head;
	t_backup	*now;
	t_backup	*temp;

	if (node_idx == 1)
	{
		free((*head)->buf);
		(*head)->buf = NULL;
		temp = (*head)->next;
		free(*head);
		*head = temp;
		return ;
	}
	now = *head;
	while (--node_idx)
	{
		pre_head = now;
		now = now->next;
	}
	pre_head->next = now->next;
	free(now->buf);
	now->buf = NULL;
	free(now);
	now = NULL;
}

char	*gnl(t_backup *head, int node_idx, int *read_size)
{
	t_backup	*pre_node;
	char		*temp_read;

	while (--node_idx)
	{
		pre_node = head;
		head = head->next;
	}
	temp_read = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_read)
		return (NULL);
	temp_read[BUFFER_SIZE] = 0;
	while (find_nl(head) == -1)
	{
		*read_size = read(head->fd, temp_read, BUFFER_SIZE);
		if (!*read_size || *read_size == -1
			|| !gnl_strjoin(head, temp_read, *read_size))
		{
			free(temp_read);
			return (NULL);
		}
	}
	free(temp_read);
	return (buf_slice(head, find_nl(head), -1, -1));
}

char	*buf_slice(t_backup *node, int nl_idx, int idx, int new_buf_idx)
{
	char	*ret;
	char	*new_buf;

	ret = (char *)malloc(nl_idx + 2);
	if (!ret)
		return (NULL);
	while (++idx <= nl_idx)
		*(ret + idx) = *(node->buf + idx);
	*(ret + idx) = 0;
	new_buf = NULL;
	if (node->buf_size - nl_idx > 1)
	{
		new_buf = (char *)malloc(sizeof(char) * (node->buf_size - nl_idx));
		if (!new_buf)
		{
			free(ret);
			return (NULL);
		}
		while ((++new_buf_idx) < node->buf_size - nl_idx - 1)
			*(new_buf + new_buf_idx) = *(node->buf + idx++);
	}
	free(node->buf);
	node->buf = new_buf;
	node->buf_size = node->buf_size - nl_idx - 1;
	return (ret);
}

int	gnl_strjoin(t_backup *node, char *temp_read, int read_size)
{
	char	*new_buf;
	int		i;
	int		j;

	new_buf = (char *)malloc(sizeof(char) * (node->buf_size + read_size + 1));
	if (!new_buf)
		return (0);
	*(new_buf + node->buf_size + read_size) = 0;
	i = -1;
	j = -1;
	while (++i < node->buf_size)
		*(new_buf + i) = *(node->buf + i);
	while (++j < read_size)
		*(new_buf + i++) = *(temp_read + j);
	node->buf_size = node->buf_size + read_size;
	if (node->buf)
	{
		free(node->buf);
		node->buf = NULL;
	}
	node->buf = new_buf;
	return (1);
}

// /////////////////////////////////////////////////
// #include <stdio.h> ///
// int main()
// {
// 	int fd[4];
// 	fd[0] = open("files/41_with_nl", O_RDWR);
// 	/* 1 */ printf("%s\n", get_next_line(1000));
//, NULL);
// 	/* 2 */ printf("%s\n", get_next_line(fd[0]));
//, "0123456789012345678901234567890123456789\n");

// 	fd[1] = open("files/42_with_nl", O_RDWR);
// 	/* 3 */ printf("%s\n", get_next_line(1001));
//, NULL);
// 	/* 4 */ printf("%s\n", get_next_line(fd[1]));
//, "01234567890123456789012345678901234567890\n");

// 	fd[2] = open("files/43_with_nl", O_RDWR);
// 	/* 5 */ printf("%s\n", get_next_line(1002));
//, NULL);
// 	/* 6 */ printf("%s\n", get_next_line(fd[2]));
// "012345678901234567890123456789012345678901\n");

// 	/* 7 */printf("%s\n", get_next_line(1003));
// NULL);
// 	/* 8 */ printf("%s\n", get_next_line(fd[0]));
// "0");
// }
// 	int fd;

// 	char *name = "./files/read_error.txt";
// 	char *other = "./files/lines_around_10.txt";
// 	int fd = open(name, O_RDONLY);
// 	int fd2 = open(other, O_RDONLY);
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd2));
// 	printf("%s\n", get_next_line(fd));
// 	printf("%s\n", get_next_line(fd2));
// 	if (BUFFER_SIZE > 100) {
// 			char *temp;
// 			do
// 			{
// 				temp = get_next_line(fd);
// 				free(temp);
// 			} while (temp != NULL);
// 		}
// 	printf("%s\n", get_next_line(fd));
// 	close(fd);
// 	printf("%s\n", get_next_line(fd2)); //90123456789\n
// 	fd = open(name, O_RDONLY);
// 	printf("%s", get_next_line(fd));//aaaaaaaaaa\n
// 	printf("%s", get_next_line(fd2)); //0123456789\n
// 	printf("%s", get_next_line(fd)); //bbbbbbbbbb\n
// 	printf("%s", get_next_line(fd)); //cccccccccc\n
// 	printf("%s", get_next_line(fd2)); //xxxx\n
// 	printf("%s", get_next_line(fd2)); //NULL
// 	printf("%s", get_next_line(fd)); //dddddddddd\n
// 	printf("%s", get_next_line(fd)); //NULL
// 	///* 1  test_gnl(fd, "aaaaaaaaaa\n");
// 	///* 2  test_gnl(fd2, "0123456789\n");
// 	///* 3  test_gnl(fd, "bbbbbbbbbb\n");
// 	///* 4  test_gnl(fd2, "012345678\n");
// 	fd = open("./files/only_nl.txt", O_RDONLY);
// 	//fd = 100;
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	return 0;
// 	}

	// TEST(/* 1 */ gnl(fd, "01234567890123456789012345678901234567890\n");
	// 	 /* 2 */ gnl(fd, "987654321098765432109876543210987654321098\n");
	// 	 /* 3 */ gnl(fd, "0123456789012345678901234567890123456789012\n");
	// 	 /* 4 */ gnl(fd, "987654321098765432109876543210987654321098\n");
	// 	 /* 5 */ gnl(fd, "01234567890123456789012345678901234567890");
	// 	 /* 6 */ gnl(fd, NULL);) close(fd);
