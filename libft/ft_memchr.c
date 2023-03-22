/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:54:46 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/21 17:03:59 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;

	temp = s;
	c = (unsigned char)c;
	while (n--)
	{
		if (*temp == c)
			return (temp);
		temp++;
	}
	return (NULL);
}
