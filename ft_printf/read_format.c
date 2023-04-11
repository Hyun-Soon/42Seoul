/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:37:33 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/10 14:43:15 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	read_format(const char *format, va_list ap)
{
	size_t	i;
	size_t	format_len;

	i = 0;
	format_len = ft_strlen(format);
	while (i < format_len)
	{
		if (!is_percent(*(format + i)))
		{
			if (write(1, format + i, 1) == -1)
				return (0);
			i++;
		}
		if (!print_conversion(*(format + i + 1), ap))
			return (0);
		i += 2;
	}
}
