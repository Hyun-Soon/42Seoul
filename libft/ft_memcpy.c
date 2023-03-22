/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:24:56 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/21 15:45:28 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// int main()
// {
// 	int arr[4] = {1,2,3,4};
// 	int arr2[4] = {6,7,8,9};

// 	size_t a;

// 	a = sizeof(arr);
// 	char *ret = ft_memcpy((void *)arr, (void *)arr2, a);

// 	printf("sizeof arr : %zu\n", a);
// 	printf("%d\n", ret[0]);
// 	printf("%d\n", ret[1]);
// 	printf("%d\n", ret[2]);
// 	printf("%d\n", ret[4]);
// 	return 0;
// }
