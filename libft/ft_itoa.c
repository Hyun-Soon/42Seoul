/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:35:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/27 16:55:50 by hyuim            ###   ########.fr       */
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

// int main()
// {
// 	char *arr = ft_itoa(1200);
// 	printf("%s", arr);
// 	return 0;
// }
