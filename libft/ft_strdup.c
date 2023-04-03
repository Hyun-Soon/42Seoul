/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:05:08 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/03 14:47:08 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc(ft_strlen(s1) + 1);
	if (ret)
	{
		while (*(s1 + i))
		{
			*(ret + i) = *(s1 + i);
			i++;
		}
		*(ret + i) = '\0';
	}
	return (ret);
}
