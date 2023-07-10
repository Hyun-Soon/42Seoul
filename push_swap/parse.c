/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 20:07:23 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/04 20:58:38 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_dup(int **arr, int inp, int arr_idx)
{
	int	idx;

	if (arr_idx == 0)
	{
		**arr = inp;
		return ;
	}
	idx = -1;
	while (++idx < arr_idx)
	{
		if (*(*arr + idx) == inp)
			ft_error(ERROR, 2);
	}
	*(*arr + arr_idx) = inp;
	return ;
}

int	*parse_input(int argc, char **argv)
{
	int	idx;
	int	inp;
	int	*ret;

	if (argc <= 2)
		exit(0);
	idx = 0;
	ret = (int *)malloc(sizeof(int) * (argc - 1));
	if (!ret)
		ft_error(ERROR, 2);
	while (++idx < argc)
	{
		inp = ft_atoi(argv[idx]);
		check_dup(&ret, inp, idx - 1);
	}
	return (ret);
}