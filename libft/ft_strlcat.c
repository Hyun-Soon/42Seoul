/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:11:31 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/24 14:04:53 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	while (*(dst + i))
	{
		i++;
	}
	while (*(src + i) && i + 1 < dstsize)
	{
		*(dst + i++) = *src++;
	}
	*(dst + i) = 0;
	if (len_dst < dstsize)
	{
		return (len_dst + len_src);
	}
	else
	{
		return (len_src + dstsize);
	}
}

// #include <stdio.h>
// int main()
// {
// 	char arr1[8] = "a";
// 	char arr2[6] = "";
// 	printf("%zu\n", ft_strlcat(arr1, arr2, 5));
// 	printf("%s\n", arr1);
// 	return (0);
// }
