/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:13 by hyuim             #+#    #+#             */
/*   Updated: 2023/05/02 13:15:43 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*backup_slice1(char **backup);
char	*backup_slice2(char **backup, int pos, int i);
int		find_nl(char *backup);
char	*gnl_strcat(char **backup, char *buf, int bytes, int i);
int		gnl_strlen(char *str);
char	*init_backup(char **backup);
void	*gnl_malloc_check(char **backup);
void	*gnl_malloc_check2(char **backup, char **ret);
char	*change_backup(char **backup, char *new_backup, char *ret);

#endif
