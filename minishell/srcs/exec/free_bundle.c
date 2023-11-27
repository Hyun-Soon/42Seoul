/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bundle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 22:31:46 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/08 21:20:11 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	free_bundle(t_bundle *bundle)
{
	int	idx;

	idx = -1;
	while (bundle->envp[++idx])
		free(bundle->envp[idx]);
	free(bundle->envp);
	return (0);
}

void	free_2d_malloced_str(char **str_arr)
{
	int	idx;

	idx = -1;
	while (str_arr[++idx])
		free(str_arr[idx]);
	free(str_arr);
}

void	free_hrdc_nodes(t_bundle *bundle)
{
	t_list		*temp;
	t_list		*temp_for_before_one;
	t_list_hrdc	*temp_hrdc;
	t_list_hrdc	*temp_for_before_hrdc_one;

	temp = bundle->hrdc_filename_list;
	while (temp)
	{
		unlink(temp->content);
		free(temp->content);
		temp->content = NULL;
		temp_for_before_one = temp;
		temp = temp->next;
		free(temp_for_before_one);
	}
	temp_hrdc = bundle->hrdc_cnt_list;
	while (temp_hrdc)
	{
		temp_for_before_hrdc_one = temp_hrdc;
		temp_hrdc = temp_hrdc->next;
		free(temp_for_before_hrdc_one);
	}
}
