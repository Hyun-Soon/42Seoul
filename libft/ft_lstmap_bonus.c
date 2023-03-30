/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:03:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/29 16:04:12 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*temp;
	t_list	*temp2;

	new_head = ft_lstnew(f(lst->content));
	if (!new_head)
		return (NULL);
	temp = new_head;
	while (lst->next)
	{
		temp2 = ft_lstnew(f(lst->next->content));
		if (!temp2)
		{
			while (new_head)
			{
				del(new_head->content);
				new_head = new_head->next;
			}
			return (NULL);
		}
		temp->next = temp2;
		temp = temp2;
	}
	return (new_head);
}
