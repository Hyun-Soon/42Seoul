/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 16:40:25 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/05 13:26:15 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ret;

	if (ft_strlen(s) < start)
	{
		ret = (char *)malloc(sizeof(char) * 1);
		if (!ret)
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	i = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	*(ret + len) = '\0';
	while (*(s + start + i) && i < len)
	{
		*(ret + i) = *(s + start + i);
		i++;
	}
	return (ret);
}
