/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_conversions2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:02:15 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/01 14:51:30 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_d(va_list ap, size_t *bytes)
{
	int		n;
	char	*ret;

	n = va_arg(ap, int);
	if (n < 0)
	{
		n *= -1;
		(*bytes)++;
		if (write(1, "-", 1) == -1)
			return (0);
	}
	ret = ltoa_base(10, (unsigned int)n);
	if (!ret)
		return (0);
	if (write(1, ret + 1, ret[0]) == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	*bytes += ret[0];
	free(ret);
	ret = NULL;
	return (1);
}

int	print_u(va_list ap, size_t *bytes)
{
	int		n;
	char	*ret;

	n = va_arg(ap, int);
	ret = ltoa_base(10, (unsigned int)n);
	if (!ret)
		return (0);
	if (write(1, ret + 1, ret[0]) == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	*bytes += ret[0];
	free(ret);
	ret = NULL;
	return (1);
}

int	print_x(va_list ap, size_t *bytes)
{
	int		n;
	char	*ret;

	n = va_arg(ap, int);
	ret = ltoa_base(16, (unsigned int)n);
	if (!ret)
		return (0);
	if (write(1, ret + 1, ret[0]) == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	*bytes += ret[0];
	free(ret);
	ret = NULL;
	return (1);
}

int	print_large_x(va_list ap, size_t *bytes)
{
	int		n;
	int		i;
	char	*ret;

	n = va_arg(ap, int);
	ret = ltoa_base(16, (unsigned int)n);
	if (!ret)
		return (0);
	i = ret[0];
	while (i > 0)
	{
		if (ret[i] >= 97 && ret[i] < 97 + 26)
			ret[i] -= ('a' - 'A');
		i--;
	}
	if (write(1, ret + 1, ret[0]) == -1)
	{
		free(ret);
		ret = NULL;
		return (0);
	}
	*bytes += ret[0];
	free(ret);
	ret = NULL;
	return (1);
}

int	print_percent(size_t *bytes)
{
	if (write(1, "%", 1) == -1)
		return (0);
	(*bytes)++;
	return (1);
}
