/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:52:35 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/14 19:19:23 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pre_exec_here_doc(t_pipe *root, t_bundle *bundle)
{
	t_list_hrdc	*new;

	if (root)
	{
		new = ft_lstnew_hrdc();
		if (!new)
			ft_error(MALLOC_ERRMSG, 1);
		ft_lstadd_back_hrdc(&(bundle->hrdc_cnt_list), new);
		if (root->cmd && root->cmd->redirect_s)
			if (search_here_doc(root->cmd->redirect_s, bundle, new) == -1)
				return (-1);
	}
	if (root->pipe)
		if (pre_exec_here_doc(root->pipe, bundle) == -1)
			return (-1);
	return (0);
}

int	search_here_doc(t_redirect_s *redirect_s,
	t_bundle *bundle, t_list_hrdc *new)
{
	if (redirect_s->redirect->type == REDIR_TWO_LEFT)
	{
		new->cnt++;
		if (exec_here_doc(redirect_s->redirect->filename, bundle) == -1)
			return (-1);
	}
	if (redirect_s->redirect_s)
		if (search_here_doc(redirect_s->redirect_s, bundle, new) == -1)
			return (-1);
	return (0);
}

char	*make_tempfile_name(void)
{
	char	*temp_filename;
	char	*temp;

	temp_filename = ft_strdup("/tmp/tmp");
	if (!temp_filename)
		ft_error(OPEN_ERRMSG, 1);
	while (!access(temp_filename, F_OK))
	{
		temp = ft_strjoin(temp_filename, "tmp");
		if (!temp)
			ft_error(MALLOC_ERRMSG, 1);
		free(temp_filename);
		temp_filename = temp;
	}
	return (temp_filename);
}

int	exec_here_doc(char *eof, t_bundle *bundle)
{
	char	*temp_filename;
	int		tempfile_fd;
	t_list	*new_node;
	int		open_flag;

	open_flag = O_RDWR | O_CREAT;
	temp_filename = make_tempfile_name();
	new_node = ft_lstnew(temp_filename);
	if (!new_node)
		ft_error(MALLOC_ERRMSG, 1);
	ft_lstadd_back(&(bundle->hrdc_filename_list), new_node);
	tempfile_fd = open(temp_filename, open_flag, 0644);
	if (write_to_tempfile_until_eof(eof, tempfile_fd) == -1)
	{
		close(tempfile_fd);
		return (-1);
	}
	if (tempfile_fd == -1)
		ft_error(OPEN_ERRMSG, 1);
	close(tempfile_fd);
	return (0);
}
