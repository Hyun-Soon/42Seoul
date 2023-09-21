/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:35:13 by hyuim             #+#    #+#             */
/*   Updated: 2023/05/25 16:07:51 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 101
# endif
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_backup
{
	int				fd;
	int				buf_size;
	char			*buf;
	struct s_backup	*next;
}	t_backup;

char	*get_next_line(int fd);
void	del_node(t_backup **head, int node_idx);
char	*gnl(t_backup *head, int node_idx, int *read_size);
char	*buf_slice(t_backup *node, int nl_idx, int idx, int new_buf_idx);
int		gnl_strjoin(t_backup *node, char *temp_read, int read_size);
int		find_nl(t_backup *node);
int		append_node(t_backup **head, int fd);
int		find_fd_node(t_backup *head, int fd);
char	*check_remain_buf(t_backup *head, int node_idx, int read_flag);
char	*clear_node(t_backup **head);

#endif
