/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:32:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/06 15:25:06 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	word_cnt(char *s, char c);
static char			*split_str(char *s, int end, char **ret, int ret_idx);
static void			put_split(char **ret, char *s, char c, int i);

char	**ft_split(char *s, char c)
{
	int		cnt;
	char	**ret;

	cnt = word_cnt(s, c);
	ret = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	*(ret + cnt) = NULL;
	put_split(ret, s, c, 0);
	if (cnt == 0)
		return (ret);
	if (!*ret)
	{
		free(ret);
		return (0);
	}
	return (ret);
}

static char	*split_str(char *s, int end, char **ret, int ret_idx)
{
	char	*spl;
	int		i;

	i = 0;
	spl = (char *)malloc((end + 2) * sizeof(char));
	if (!spl)
	{
		while (ret_idx--)
		{
			free(*(ret + ret_idx));
			*(ret + ret_idx) = NULL;
		}
		return (NULL);
	}
	*(spl + (end + 1)) = 0;
	while (i <= end)
	{
		*(spl + i) = *(s + i);
		i++;
	}
	return (spl);
}

static void	put_split(char **ret, char *s, char c, int i)
{
	int	end;

	end = 0;
	while (*s)
	{
		if (*s == c && end == 0)
		{
			s++;
			continue ;
		}
		else if (*(s + end) != c
			&& (*(s + end + 1) == c || *(s + end + 1) == 0))
		{
			*(ret + i) = split_str(s, end, ret, i);
			if (*(ret + i) == NULL)
				return ;
			i++;
			s = s + end + 1;
			end = 0;
			continue ;
		}
		end++;
	}
}

static unsigned int	word_cnt(char *s, char c)
{
	unsigned int	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c
			&& (*(s + 1) == c || *(s + 1) == 0))
			cnt++;
		s++;
	}
	return (cnt);
}
