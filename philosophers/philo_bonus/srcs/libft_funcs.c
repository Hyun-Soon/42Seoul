/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:21:06 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/30 21:07:56 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

size_t	ft_strlen(const char *s)
{
	int	cnt;

	cnt = 0;
	while (*(s + cnt))
		cnt++;
	return (cnt);
}

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

int	ft_atoi(const char *str)
{
	int		sign;
	long	ret;

	ret = 0;
	sign = 1;
	if (*str == 0)
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		ret = ret * 10 + (long)(*str - '0');
		if (ret < -2147483648 || ret > 2147483647)
			return (-1);
		str++;
	}
	ret = sign * ret;
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (*(src + i) && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	while (*(src + i))
		i++;
	return (i);
}

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
