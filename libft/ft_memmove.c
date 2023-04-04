/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:24:42 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/04 16:57:16 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_;
	const char	*src_;

	if (!dst && !src)
		return (NULL);
	dst_ = (char *)dst;
	src_ = (const char *)src;
	if (dst_ <= src_)
	{
		while (len--)
		{
			*dst_++ = *src_++;
		}
	}
	else
	{
		while (len--)
			*(dst_ + len) = *(src_ + len);
	}
	return (dst);
}
