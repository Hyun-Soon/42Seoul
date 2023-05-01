/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 20:20:58 by hyuim             #+#    #+#             */
/*   Updated: 2023/05/01 22:18:22 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> ///

char	*get_next_line(int fd)
{
	int			read_size;
	char		buf[BUFFER_SIZE + 1];
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size > 0)
		buf[read_size] = 0;
	while (read_size >= 0)
	{
		if (read_size)
			backup = gnl_strcat(backup, buf, read_size);
		else if (find_nl(backup) == -1)
			return (backup_slice1(&backup)); //backup = NULL로 만들고 backup에 남아있는 애들 리턴해주기
		if (find_nl(backup) >= 0)
			return (backup_slice2(&backup, find_nl(backup), -1)); //bakcup에서 \n까지 자르고 나머지 backup에 업데이트 해주기
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size != -1)
			buf[read_size] = 0;
	}
	return (init_backup(&backup));
}

char	*init_backup(char **backup)
{
	int	len;
	int	i;

	len = gnl_strlen(*backup);
	i = 0;
	while (i < len)
	{
		*(*backup + i) = 0;
		i++;
	}
	free(*backup);
	*backup = NULL;
	return (NULL);
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

// int main()
// {
// 	int fd;


// 	fd = open("./files/test.txt", O_RDONLY);
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
