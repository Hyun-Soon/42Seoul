/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 15:03:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/05 13:37:44 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*start;
	void	*temp;

	if (!lst)
		return (NULL);
	temp = f(lst->content);
	new_list = ft_lstnew(temp);
	if (!new_list)
		free(temp);
	start = new_list;
	while (lst->next && start)
	{
		lst = lst->next;
		temp = f(lst->content);
		new_list->next = ft_lstnew(temp);
		new_list = new_list->next;
		if (!new_list)
		{
			del(temp);
			ft_lstclear(&start, del);
			return (NULL);
		}
	}
	return (start);
}
