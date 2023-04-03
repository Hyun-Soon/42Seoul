/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:32:17 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/03 20:45:48 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	word_cnt(char *str, char c);
int				is_sep(char c, char *charset);
char			*split_str(char *str, int end, char **ret, int ret_idx);
void			put_split(char **ret, char *str, char c, int i);

char	**ft_split(char *str, char c)
{
	int		cnt;
	char	**ret;

	cnt = word_cnt(str, c);
	ret = (char **)malloc((cnt + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	*(ret + cnt) = NULL;
	put_split(ret, str, c, 0);
	if (cnt == 0)
		return (ret);
	if (!*ret)
	{
		free(ret);
		return (0);
	}
	return (ret);
}

char	*split_str(char *str, int end, char **ret, int ret_idx)
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
		*(spl + i) = *(str + i);
		i++;
	}
	return (spl);
}

void	put_split(char **ret, char *str, char c, int i)
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
			&& (*(str + end + 1) == c || *(str + end + 1) == 0))
		{
			*(ret + i) = split_str(str, end, ret, i);
			if (*(ret + i) == NULL)
				return ;
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
