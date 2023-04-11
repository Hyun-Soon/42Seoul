/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_conversions1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:09:11 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/11 13:19:06 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_conversion(char c, va_list ap)
{
	if (c == 'c')
		return (print_c(ap));
	else if (c == 's')
		return (print_s(ap));
	else if (c == 'p')
		return (print_p(ap));
	else if (c == 'd' || c == 'i')
		return (print_d(ap));
	else if (c == 'u')
		return (print_u(ap));
	else if (c == 'x')
		return (print_x(ap));
	else if (c == 'X')
		return (print_X(ap));
	else if (c == '%')
		return (print_percent());
	else
		return (0);
}

int	print_c(va_list ap)
{
	char	c;

	c = va_arg(ap, char);
	return (write(1, &c, 1));
}

int	print_s(va_list ap)
{
	const char	*str;
	size_t		len;

	str = va_arg(ap, const char *);
	len = ft_strlen(str);
	if (write(1, &str, len) == -1)
		return (0);
	return (1);
}

int	print_p(va_list ap)
{
	unsigned long	addr;
	char			*ret;

	addr = va_arg(ap, unsigned long);
	ret = ltoa_base(16, addr);
	if (write(1, "0x", 2) == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	if (write(1, ret + 1, ret[0] - '0') == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	return (1);
}

char	*ltoa_base(int base, unsigned long n)
{
	char			*ret;
	char			*base_str;
	unsigned long	temp;
	int				i;

	i = 1;
	base_str = "0123456789abcdefghijklmnopqrstuvwxyz";
	while (temp)
	{
		i++;
		temp /= base;
	}
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
