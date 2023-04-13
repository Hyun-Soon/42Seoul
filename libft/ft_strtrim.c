/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 16:17:09 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/06 15:13:56 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s1, char const *set);
static int	find_end(char const *s1, char const *set);
static int	ft_isin(char c, char *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		start;
	int		end;

	start = find_start(s1, set);
	end = find_end(s1, set);
	if (start > end)
	{
		ret = (char *)malloc(sizeof(char) * 1);
		if (!ret)
			return (NULL);
		*ret = '\0';
		return (ret);
	}
	ret = ft_substr(s1, start, end - start + 1);
	return (ret);
}

static int	find_start(char const *s1, char const *set)
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

static int	find_end(char const *s1, char const *set)
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

static int	ft_isin(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
