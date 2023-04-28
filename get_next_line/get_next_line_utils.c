/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:14:24 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/28 20:17:06 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_nl(char *backup)
{
	int	i;

	i = 0;
	while (*(backup + i))
	{
		if (*(backup + i) == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
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

char	*backup_slice(char **backup, int pos)
{
	int		i;
	int		new_backup_len;
	char	*new_backup;
	char	*ret;

	ret = (char *)malloc(sizeof(char) * pos);
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < pos)
		*(ret + i) = *(*backup + i);
	new_backup_len = gnl_strlen(*backup) - pos + 1;
	new_backup = (char *)malloc(sizeof(char) * new_backup_len);
	if (!new_backup)
		return (NULL);
	i = -1;
	while (++i < new_backup_len - 1)
		*(new_backup + i) = *(*backup + pos + i);
	*(new_backup + i) = '\0';
	free(*backup);
	*backup = new_backup;
	return (ret);
}
