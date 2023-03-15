/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:24:56 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/15 19:43:27 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{

	size_t i;

	i = 0;
	while (i != n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return dst;    
}

//TODO : study how can solve it with restrict
#include <stdio.h>
int main()
{
	char *arr = "abc";
	char *arr2 = "aaa";

	unsigned int a = 3;

	char *ret = ft_memcpy(arr, arr2, a);

	printf("%c", *ret);
	return 0;
}