/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:20:58 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/28 21:41:53 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			read_size;
	char		buf[BUFFER_SIZE + 1];
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size == -1)
		return (NULL);
	while (read_size >= 0)
	{
		if (read_size)
			backup = gnl_strcat(backup, buf, read_size);
		if (find_nl(backup) == -1 && !read_size)
			return (backup_slice1(&backup)); //backup = NULL로 만들고 backup에 남아있는 애들 리턴해주기
		if (find_nl(backup) >= 0)
			return (backup_slice2(&backup, find_nl(backup))); //bakcup에서 \n까지 자르고 나머지 backup에 업데이트 해주기
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
	}
	return (NULL);
}

char	*backup_slice2(char **backup, int nl_idx)
{
	int		i;
	int		new_backup_len;
	char	*new_backup;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (nl_idx + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < nl_idx + 1)
		*(ret + i) = *(*backup + i);
	new_backup_len = gnl_strlen(*backup) - nl_idx;
	new_backup = (char *)malloc(sizeof(char) * new_backup_len);
	if (!new_backup)
		return (NULL);
	i = -1;
	while (++i < new_backup_len)
		*(new_backup + i) = *(*backup + nl_idx + i + 1);
	free(*backup);
	*backup = new_backup;
	return (ret);
}

char	*backup_slice1(char **backup)
{
	char	*ret;
	int		len;
	int		i;

	if (*backup == NULL)
		return (NULL);
	len = gnl_strlen(*backup);
	ret = (char *)malloc(sizeof(char) * len);
	if (!ret)
		return (NULL);
	i = 0;
	while (len--)
	{
		*(ret + i) = *(*backup + i);
		i++;
	}
	free(*backup);
	*backup = NULL;
	return (ret);
}

char	*gnl_strcat(char *backup, char *buf, int bytes)
{
	int		i;
	int		j;
	int		backup_len;
	char	*ret;

	backup_len = gnl_strlen(backup);
	ret = (char *)malloc(sizeof(char) * (backup_len + bytes + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (i < backup_len)
	{
		*(ret + i) = *(backup + i);
		i++;
	}
	while (j < bytes)
	{
		*(ret + i) = *(buf + j);
		i++;
		j++;
	}
	*(ret + i) = 0;
	free(backup);
	return (ret);
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
