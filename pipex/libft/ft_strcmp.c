/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:25:43 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/29 21:05:26 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	idx;

	idx = 0;
	while (*(str1 + idx) && *(str2 + idx))
	{
		if (*(str1 + idx) != *(str2 + idx))
			return (*(str1 + idx) - *(str2 - idx));
		idx++;
	}
	return (*(str1 + idx) - *(str2 + idx));
}
