/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:40:25 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/24 14:04:01 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	sub_len;
	char	*ret;

	i = 0;
	sub_len = ft_strlen(s + start);
	if (len < sub_len)
		sub_len = len;
	ret = (char *)malloc(sizeof(char) * (sub_len + 1));
	if (ret)
	{
		while (*(s + i) && i < sub_len)
		{
			*(ret + i) = *(s + i);
			i++;
		}
	}
	return (ret);
}
