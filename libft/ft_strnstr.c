/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:17:39 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/22 18:33:21 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	limit;
	unsigned int	needle_len;
	unsigned int	flag;

	if (!*needle)
		return (haystack);
	i = 0;
	flag = 0;
	needle_len = ft_strlen(needle);
	limit = len - needle_len;
	while (i <= limit && *(haystack + i))
	{
		if (*(haystack + i) == *(needle + i))
		{
			if (strncmp(haystack + i, needle, needle_len) == 0)
				return (haystack + i);
		}
		i++;
	}
	return (NULL);
}
