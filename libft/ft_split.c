/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:32:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/27 15:39:24 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	word_cnt(char *str, char c);
int				is_sep(char c, char *charset);
char			*split_str(char *str, int end);
void			put_split(char **ret, char *str, char *charset, int i);

char	**ft_split(char *str, char c)
{
	int		cnt;
	char	**ret;

	cnt = word_cnt(str, c);
	ret = (char **)malloc((cnt + 1) * sizeof(char *));
	*(ret + cnt) = NULL;
	put_split(ret, str, charset, 0);
	return (ret);
}

char	*split_str(char *str, int end)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)malloc((end + 2) * sizeof(char));
	*(ret + (end + 1)) = 0;
	while (i <= end)
	{
		*(ret + i) = *(str + i);
		i++;
	}
	return (ret);
}

void	put_split(char **ret, char *str, char *charset, int i)
{
	int	end;

	end = 0;
	while (*str)
	{
		if (*str == c && end == 0)
		{
			str++;
			continue ;
		}
		else if (*(str + end) != c
			&& (*(str + end + 1) == c
				|| *(str + end + 1) == 0))
		{
			*(ret + i) = split_str(str, end);
			i++;
			str = str + end + 1;
			end = 0;
			continue ;
		}
		end++;
	}
}

unsigned int	word_cnt(char *str, char c)
{
	unsigned int	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != c
			&& (*(str + 1) == c || *(str + 1) == 0))
			cnt++;
		str++;
	}
	return (cnt);
}

int	is_sep(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}
