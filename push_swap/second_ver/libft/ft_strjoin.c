/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:59:34 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/03 16:12:09 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret)
	{
		while (*(s1 + i))
		{
			*(ret + i) = *(s1 + i);
			i++;
		}
		while (*(s2 + j))
		{
			*(ret + i) = *(s2 + j);
			i++;
			j++;
		}
		*(ret + i) = '\0';
	}
	return (ret);
}
