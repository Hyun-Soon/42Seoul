/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:24:42 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/22 19:50:32 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst_;
	const char	*src_;

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
		{
			*(dst_ + len) = *(src_ + len);
		}
	}
	return (dst);
}

// #include <stdio.h>
// int main()
// {
// 	char arr[] = "Hello, world!";

// 	ft_memmove(arr + 2, arr, 2);
// 	printf("%s", arr);
// 	return 0;
// }
