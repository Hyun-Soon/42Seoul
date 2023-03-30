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

#include <stdio.h>
int main(void)
{
	char *input1 = "-9223372036854775808";
	char *input2 = "-9223372036854775809";
	char *input3 = "-9223372036854775810";
	char *input4 = "9223372036854775807";
	char *input5 = "9223372036854775808";
	char *input6 = "9223372036854775809";


	printf("min atoi : %d\n", atoi(input1));
	printf("min atoi - 1 : %d\n", atoi(input2));
	printf("min atoi - 2 : %d\n\n", atoi(input3));

	printf("min ft_atoi : %d\n", ft_atoi(input1));
	printf("min ft_atoi - 1: %d\n", ft_atoi(input2));
	printf("min ft_atoi - 2: %d\n\n", ft_atoi(input3));

	printf("max atoi : %d\n", atoi(input4));
	printf("max atoi + 1 : %d\n", atoi(input5));
	printf("max atoi + 2 : %d\n\n", atoi(input6));

	printf("max ft_atoi : %d\n", ft_atoi(input4));
	printf("max ft_atoi + 1: %d\n", ft_atoi(input5));
	printf("max ft_atoi + 2: %d\n\n", ft_atoi(input6));

	printf("%d\n", (int)LONG_MAX);
	printf("%d\n", (int)LONG_MIN);

// 	char *inp1 = "-2147483649";
// 	char *inp2 = "2147483648";
// 	printf("%d\n", atoi(inp1));
// 	printf("%d\n", atoi(inp2));
// 	printf("%d\n", ft_atoi(inp1));
// 	printf("%d\n", ft_atoi(inp2));
}
