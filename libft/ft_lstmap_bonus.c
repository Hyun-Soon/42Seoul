/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:03:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/04 15:41:23 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*start;

	if (!lst)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	start = new_list;
	while (lst->next)
	{
		lst = lst->next;
		new_list->next = ft_lstnew(f(lst->content));
		new_list = new_list->next;
		if (!new_list)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
	}
	return (start);
}
