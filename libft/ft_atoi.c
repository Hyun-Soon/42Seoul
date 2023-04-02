/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:51:40 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/30 10:13:47 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				sign;
	unsigned long	ret;

	ret = 0;
	sign = 1;
	while (*str >= 9 && (*str <= 13 || *str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + (unsigned long)(*str - '0');
		str++;
	}
	if (ret > LONG_MAX)
	{
		if (sign == 1)
			return ((int)LONG_MAX);
		return ((int)LONG_MIN);
	}
	return (sign * (long)ret);
}
