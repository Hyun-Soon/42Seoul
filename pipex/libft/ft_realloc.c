/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:04:21 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/27 19:56:00 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(t_bundle *bundle, int org_size, void *org_ptr, int new_size)
{
	void	*ret;

	if (!org_ptr)
		return (malloc(new_size * sizeof(char)));
	if (!org_size)
		free(org_ptr);
	ret = malloc(sizeof(char) * new_size);
	if (!ret)
		ft_error("Malloc Error from realloc\n", -1, bundle, 2);
	ft_memcpy(ret, org_ptr, org_size);
	free(org_ptr);
	return (ret);
}
