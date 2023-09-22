/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:04:21 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/22 10:35:28 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(int org_size, void *org_ptr, int new_size)
{
	void	*ret;

	if (!org_ptr)
		return (malloc(new_size * sizeof(int)));
	if (!org_size)
		free(org_ptr);
	ret = malloc(new_size);
	if (!ret)
		exit(1);
	ft_memcpy(ret, org_ptr, org_size);
	free(org_ptr);
	return (ret);
}
