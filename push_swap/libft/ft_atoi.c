/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:51:40 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/10 17:31:04 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	ret;

	ret = 0;
	sign = 1;
	if (*str == 0)
		ft_error(ERROR, 2);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			ft_error(ERROR, 2);
		ret = ret * 10 + (long)(*str - '0');
		str++;
	}
	ret = sign * ret;
	if (ret < -2147483648 || ret > 2147483647)
		ft_error(ERROR, 2);
	return (ret);
}
