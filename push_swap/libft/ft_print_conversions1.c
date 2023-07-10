/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conversions1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:09:11 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/01 14:51:25 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_conversion(char c, va_list ap, size_t *bytes)
{
	if (c == 'c')
		return (print_c(ap, bytes));
	else if (c == 's')
		return (print_s(ap, bytes));
	else if (c == 'p')
		return (print_p(ap, bytes));
	else if (c == 'd' || c == 'i')
		return (print_d(ap, bytes));
	else if (c == 'u')
		return (print_u(ap, bytes));
	else if (c == 'x')
		return (print_x(ap, bytes));
	else if (c == 'X')
		return (print_large_x(ap, bytes));
	else if (c == '%')
		return (print_percent(bytes));
	else
		return (0);
}

int	print_c(va_list ap, size_t *bytes)
{
	char	c;

	c = va_arg(ap, int);
	if (write(1, &c, 1) == -1)
		return (0);
	(*bytes)++;
	return (1);
}

int	print_s(va_list ap, size_t *bytes)
{
	const char	*str;
	size_t		len;

	str = va_arg(ap, const char *);
	if (!str)
	{
		if (write(1, "(null)", 6) == -1)
			return (0);
		*bytes += 6;
		return (1);
	}
	len = ft_strlen(str);
	if (write(1, str, len) == -1)
		return (0);
	*bytes += len;
	return (1);
}

int	print_p(va_list ap, size_t *bytes)
{
	unsigned long	addr;
	char			*ret;

	addr = va_arg(ap, unsigned long);
	ret = ltoa_base(16, addr);
	if (!ret)
		return (0);
	if (write(1, "0x", 2) == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	if (write(1, ret + 1, ret[0]) == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	*bytes += ret[0] + 2;
	free(ret);
	ret = NULL;
	return (1);
}

char	*ltoa_base(int base, unsigned long n)
{
	char			*ret;
	char			*base_str;
	unsigned long	temp;
	int				i;

	i = 1;
	temp = n;
	base_str = "0123456789abcdefghijklmnopqrstuvwxyz";
	while (temp)
	{
		i++;
		temp /= base;
	}
	if (i == 1)
		i++;
	ret = (char *)malloc(sizeof(char) * i);
	if (!ret)
		return (NULL);
	ret[0] = i - 1;
	while (i > 1)
	{
		ret[--i] = base_str[n % base];
		n /= base;
	}
	return (ret);
}
