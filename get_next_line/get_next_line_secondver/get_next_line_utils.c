/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 21:41:25 by hyuim             #+#    #+#             */
/*   Updated: 2023/05/01 21:13:07 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	find_nl(char *backup)
{
	int	i;

	if (!backup)
		return (0); //파일 끝에서 실행했을 때를 위해
	i = 0;
	while (*(backup + i))
	{
		if (*(backup + i) == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*backup_slice2(char **backup, int nl_idx, int i)
{
	int		new_backup_len;
	char	*new_backup;
	char	*ret;

	if (!*backup)
		return (NULL); //파일 끝에서 실행했을 때를 위해
	ret = (char *)malloc(sizeof(char) * (nl_idx + 2));
	if (!ret)
		return (NULL);
	while (++i < nl_idx + 1)
		*(ret + i) = *(*backup + i);
	*(ret + i) = 0;
	new_backup_len = gnl_strlen(*backup) - nl_idx;
	if (new_backup_len == 1)
		new_backup = NULL;
	else
	{
		new_backup = (char *)malloc(sizeof(char) * new_backup_len);
		if (!new_backup)
			return (NULL);
		i = -1;
		while (++i < new_backup_len)
			*(new_backup + i) = *(*backup + nl_idx + i + 1);
	}
	free(*backup);
	*backup = new_backup;
	return (ret);
}

char	*backup_slice1(char **backup)
{ // no nl의 경우 원래 있던 backup의 메모리 주소를 리턴해줘야 한다..
	char	*ret;
	int		len;
	int		i;

	if (*backup == NULL)
		return (NULL);
	len = gnl_strlen(*backup);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (len--)
	{
		*(ret + i) = *(*backup + i);
		i++;
	}
	*(ret + i) = 0;
	free(*backup);
	*backup = NULL;
	return (ret);
} //리턴값 뒤에 null(0)을 줘야 한다.
  //backup은 마지막에 free를시켜주기 때문에 backup_slice1의 경우 따로 문자열 만들고 리턴해줘야 한다.

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
