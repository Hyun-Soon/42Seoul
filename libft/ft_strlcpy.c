/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:37:08 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/21 14:37:10 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t len;

	i = 0;
	while (*(src + i) && i < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	len = i;
	while (i != dstsize)
	{
		*(dst + i++) = 0;
	}
	return (len);
}


// #include <stdio.h>
// int main()
// {
// 	char arr[5];
// 	char src[] = "abc";

// 	int ret = ft_strlcpy(arr, src, 5);
// 	printf("%d\n", *(src + 3));
// 	printf("%s\n", arr);
// 	printf("%d", ret);
// 	return 0;
// }
