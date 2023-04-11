/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversions2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:02:15 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/10 19:45:37 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_d(va_list ap)
{
	int		n;
	char	*ret;

	n = va_arg(ap, int);
	ret = ltoa_base(10, (unsigned long)n);
	if (n < 0)
		if (write(1, "-", 1) == -1)
			return (0);
	if (write(1, ret + 1, ret[0] - '0') == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	return (1);
}

int	print_u(va_list ap)
{
	int		n;
	char	*ret;

	n = va_arg(ap, int);
	ret = ltoa_base(10, n);
	if (write(1, ret + 1, ret[0] - '0') == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	return (1);
}

int	print_x(va_list ap)
{
	int		n;
	char	*ret;

	n = va_arg(ap, int);
	ret = ltoa_base(16, n);
	if (write(1, ret + 1, ret[0] - '0') == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	return (1);
}

int	print_X(va_list ap)
{
	int		n;
	int		i;
	char	*ret;

	n = va_arg(ap, int);
	ret = ltoa_base(16, n);
	if (!ret)
		return (0);
	i = ret[0] - '0';
	while (i > 0)
		ret[i--] += 26;
	if (write(1, ret + 1, ret[0] - '0') == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	return (1);
}

int	print_percent(void)
{
	if (write(1, "%", 1) == -1)
		return (0);
	return (1);
}
