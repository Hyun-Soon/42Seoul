/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:07:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/20 21:58:35 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_dup(int *arr, int inp, int arr_idx)
{
	int	idx;

	if (arr_idx == 0)
	{
		*arr = inp;
		return ;
	}
	idx = -1;
	while (++idx < arr_idx)
	{
		if (*(arr + idx) == inp)
		{
			free(arr);
			ft_error(ERROR, 2);
		}
	}
	*(arr + arr_idx) = inp;
	return ;
}

int	*parse_input(int argc, char **argv, int *ret_size)
{
	int		temp_idx;
	char	**split_ret;
	int		split_idx;
	int		inp;
	int		atoi_flag;
	int		*ret;

	temp_idx = 0;
	atoi_flag = 0;
	split_ret = NULL;
	ret = NULL;
	while (++temp_idx < argc)
	{
		split_idx = -1;
		split_ret = ft_split(argv[temp_idx], ' ');
		while (split_ret[++split_idx])
		{
			inp = ft_ps_atoi(split_ret[split_idx], &atoi_flag);
			ret = ft_realloc(*ret_size  * sizeof(int), ret, (*ret_size + 1) * sizeof(int));
			check_dup(ret, inp, *ret_size);
			*ret_size += 1;
		}
		free_split_ret(split_ret);
	}
	return (ret);
}

int	ft_ps_atoi(const char *str, int *atoi_flag)
{
	int		sign;
	long	ret;

	ret = 0;
	sign = 1;
	if (*str == 0)
		*atoi_flag = -1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			*atoi_flag = -1;
		ret = ret * 10 + (long)(*str - '0');
		str++;
	}
	ret = sign * ret;
	if (ret < -2147483648 || ret > 2147483647)
		*atoi_flag = -1;
	return (ret);
}

void	free_split_ret(char **split_ret)
{
	int	i;

	if (!split_ret)
		return ;
	i = -1;
	while (split_ret[++i])
		free(split_ret[i]);
	free(split_ret);
}