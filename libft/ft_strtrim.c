/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:17:09 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/27 13:27:49 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_start(char const *s1, char const *set);
int	find_end(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;
	int		start;
	int		end;

	start = find_start(s1, set);
	end = find_end(s1, set);
	if (start > end)
	{
		ret = (char *)malloc(sizeof(char));
		if (!ret)
			*ret = '\0';
		return (ret);
	}
	ret = (char *)malloc(sizeof(char) * (start - end + 2));
	if (!ret)
	{
		i = 0;
		while (start <= end)
		{
			*(ret + i) = *(s1 + start);
			start++;
			i++;
		}
		*(ret + i) = '\0';
	}
	return (ret);
}

int	find_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (*(s1 + i))
	{
		if (!ft_isin(*(s1 + i), (char *)set))
			return (i);
		i++;
	}
	return (i);
}

int	find_end(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i > -1)
	{
		if (!ft_isin(*(s1 + i), (char *)set))
			return (i);
		i--;
	}
	return (i);
}
