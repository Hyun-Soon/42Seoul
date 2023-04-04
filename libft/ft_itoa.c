/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:35:03 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/04 13:37:45 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_digits(int n);
void	put_int_min(char *ret);
void	put_n(int digits, int n, int sign, char *ret);

char	*ft_itoa(int n)
{
	char	*ret;
	int		digits;
	int		sign;

	sign = 1;
	digits = get_digits(n);
	ret = (char *)malloc(sizeof(char) * (digits + 1));
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		*ret = '-';
		sign = -1;
	}
	*(ret + digits) = '\0';
	if (n == 0)
	{
		*ret = '0';
		return (ret);
	}
	put_n(digits, n, sign, ret);
	return (ret);
}

void	put_n(int digits, int n, int sign, char *ret)
{
	while (digits-- && n)
	{
		*(ret + digits) = n % 10 * sign + '0';
		n /= 10;
	}
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
