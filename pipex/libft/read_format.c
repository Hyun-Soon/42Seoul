/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:37:33 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/26 17:52:19 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	read_format(const char *format, va_list ap)
{
	size_t	i;
	size_t	format_len;
	size_t	bytes;

	i = 0;
	bytes = 0;
	format_len = ft_strlen(format);
	while (i < format_len)
	{
		if (!is_percent(*(format + i)))
		{
			if (write(1, format + i, 1) == -1)
				return (-1);
			bytes++;
			i++;
			continue ;
		}
		if (!print_conversion(*(format + i + 1), ap, &bytes))
			return (-1);
		i += 2;
	}
	return (bytes);
}

size_t	ft_strlen(const char *s)
{
	int	cnt;

	cnt = 0;
	while (*(s + cnt))
		cnt++;
	return (cnt);
}
