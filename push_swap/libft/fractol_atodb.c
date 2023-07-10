/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_atodb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 17:04:13 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/29 21:00:46 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_valid_double(const char *str)
{
	int	point;
	int	idx;

	idx = 0;
	point = 0;
	while (*(str + idx))
	{
		if (*(str + idx) == '.')
			point++;
		else if (*(str + idx) == '-')
			;
		else if (*(str + idx) < '0' || *(str + idx) > '9')
			return (-1);
		idx++;
	}
	if (point > 1)
		return (-1);
	return (1);
}

static double	get_db(const char *str, int idx)
{
	int		point_flag;
	double	integer;
	double	rational;

	point_flag = 0;
	integer = 0;
	rational = 0;
	while (*(str + idx))
	{
		if (*(str + idx) == '.')
			point_flag = 1;
		else if (point_flag == 0)
			integer = integer * 10 + (*(str + idx) - '0');
		else
			rational = rational * 0.1 + ((*(str + idx) - '0') * 0.1);
		idx++;
	}
	return (integer + rational);
}

double	fractol_atodb(const char *str)
{
	int		sign;
	int		idx;
	double	ret;

	if (check_valid_double(str) == -1)
		ft_error("invalid input for complex number!", 2);
	idx = 0;
	sign = 1;
	if (*(str) == '-')
	{
		sign = -1;
		idx++;
	}
	ret = get_db(str, idx);
	ret *= sign;
	return (ret);
}
