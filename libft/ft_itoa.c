/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:35:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/29 16:17:44 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		cnt;
	char	*ret;
	int		i;
	int		temp;

	cnt = 0;
	i = 0;
	temp = ft_abs(n);
	if (n < 0)
		cnt++;
	while (temp > 0)
	{
		temp /= 10;
		cnt++;
	}
	ret = (char *)malloc(sizeof(char) * (cnt + 1));
	*(ret + cnt) = 0;
	while (cnt--)
	{
		*(ret + cnt) = (ft_abs(n) % 10) + '0';
		n /= 10;
	}
	if (*ret == '0')
		*ret = '-';
	return (ret);
}

// #include <stdio.h>
// int main()
// {
// 	char *arr = ft_itoa(1200);
// 	char *arr2 = ft_itoa(LONG_MAX);
// 	char *arr3 = itoa(1200);
// 	char *arr4 = itoa(LONG_MAX);
// 	printf("%s\n", arr);
// 	printf("%s\n", arr2);
// 	printf("%s\n", arr3);
// 	printf("%s\n", arr4);
// 	return 0;
// }
