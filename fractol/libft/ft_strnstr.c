/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:17:39 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/04 17:27:16 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	limit;
	unsigned int	needle_len;

	if (!*haystack && !*needle)
		return ((char *)haystack);
	if (!*needle)
		return ((char *)haystack);
	i = 0;
	needle_len = ft_strlen(needle);
	if (len < needle_len)
		return (NULL);
	limit = len - needle_len;
	while (i <= limit && *(haystack + i))
	{
		if (*(haystack + i) == *needle)
		{
			if (ft_strncmp(haystack + i, needle, needle_len) == 0)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
