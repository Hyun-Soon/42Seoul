/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:05:27 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/08 11:33:38 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst)
{
	t_list *temp;

	temp = lst;
	lst->prev->next = temp->next;
	lst->next->prev = temp->prev;
	free(temp);
	return ;
}
