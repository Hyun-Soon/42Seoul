/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:18:08 by hyuim             #+#    #+#             */
/*   Updated: 2023/08/11 15:30:44 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int base, int exponent)
{
	if (base == 0)
		return (0);
	if (exponent == 0)
		return (1);
	return (base * ft_pow(base, exponent - 1));
}