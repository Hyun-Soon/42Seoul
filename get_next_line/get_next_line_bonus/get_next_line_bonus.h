/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:13 by hyuim             #+#    #+#             */
/*   Updated: 2023/05/22 17:20:12 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_backup
{
	int				fd;
	char			*buf;
	struct s_backup	*next;
}	t_backup;

char	*get_next_line(int fd);
int		append_node(t_backup **head, int fd);
char	*gnl(t_backup *head, int node_idx);
char	*buf_slice(char **buf, int nl_idx);
char	*ft_strjoin(char *buf, char *temp_read);
int		find_fd_node(t_backup *head, int fd);
int		gnl_strlen(char *str);
int		find_nl(char *buf);
void	*del_node(t_backup *head, int node_idx);

#endif
