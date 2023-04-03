/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:35:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/03 19:51:15 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		get_digits(int n);
void	put_int_min(char *ret);

char	*ft_itoa(int n)
{
	char	*ret;
	int		digits;
	int		sign;

	sign = 1;
	digits = get_digits(n);
	ret = (char *)malloc(sizeof(char) * (digits + 1));
	if (n < 0)
	{
		*ret = '-';
		sign = -1;
	}
	*(ret + digits) = '\0';
	while (digits-- && n)
	{
		*(ret + digits) = n % 10 * sign + '0';
		n /= 10;
	}
	return (ret);
}

int	get_digits(int n)
{
	int	temp;
	int	cnt;

	cnt = 0;
	if (n == -2147483648)
		return (11);
	temp = ft_abs(n);
	while (temp > 0)
	{
		temp /= 10;
		cnt++;
	}
	if (n <= 0)
		cnt++;
	return (cnt);
}

int main()
{
	printf("%s\n", ft_itoa(0));
	return 0;
}
