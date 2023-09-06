/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:17:29 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/22 18:31:36 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char			*ret;
	unsigned int	i;

	i = 0;
	ret = (char *)malloc(count * size);
	if (ret)
	{
		while (i < count * size)
		{
			*(ret + i) = 0;
			i++;
		}
	}
	return ((void *)ret);
}
