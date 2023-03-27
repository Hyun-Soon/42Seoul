/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:56:32 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/27 19:43:16 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ret;

	i = 0;
	while (*(s + i))
		i++;
	ret = (char *)malloc(sizeof(char) * (i + 1));
	*(ret + i) = 0;
	i = 0;
	while (*(ret + i))
	{
		*(ret + i) = f(i, *(s + i));
		i++;
	}
	return (ret);
}
