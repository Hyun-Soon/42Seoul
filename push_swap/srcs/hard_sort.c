/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hard_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:58:13 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/11 13:33:29 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	hard_sort(int *inp_list, int inp_size, t_stacks *stks, t_dll *stk)
{
	if (inp_size <= 2)
		sort_2args(stk);
	else if (inp_size <= 3)
		sort_3args(stk);
	else if (inp_size <= 4)
		sort_4args(inp_list, inp_size, stks);
	else
		sort_5args(inp_list, inp_size, stks);
	exit(0);
}

void	sort_2args(t_dll *stk)
{
	if (stk->value > stk->next->value)
		ft_printf("%s", "sa");
}

void	sort_3args(t_dll *stk)
{
	if (stk->value < stk->next->value
		&& stk->value < stk->next->next->value
		&& stk->next->value > stk->next->next->value)
		ft_printf("%s\n%s\n", "rra", "sa");
	else if (stk->value > stk->next->value
		&& stk->next->value < stk->next->next->value
		&& stk->value < stk->next->next->value)
		ft_printf("%s\n", "sa");
	else if (stk->value < stk->next->value
		&& stk->next->value > stk->next->next->value
		&& stk->value > stk->next->next->value)
		ft_printf("%s\n", "rra");
	else if (stk->value > stk->next->value
		&& stk->value > stk->next->next->value
		&& stk->next->value < stk->next->next->value)
		ft_printf("%s\n", "ra");
	else if (stk->value > stk->next->value
		&& stk->next->value > stk->next->next->value)
		ft_printf("%s\n%s\n", "sa", "rra");
}

void	sort_4args(int *inp_list, int inp_list_size, t_stacks *stks)
{
	int	arr[4];

	sort_ascend(inp_list, inp_list_size, arr);
	while (stks->stk_a->value != arr[0])
	{
		ft_rotate(stks, RA);
		ft_printf("ra\n");
	}
	ft_push(stks, PB);
	ft_printf("pb\n");
	sort_3args(stks->stk_a);
	ft_printf("pa\n");
}

void	sort_5args(int *inp_list, int inp_list_size, t_stacks *stks)
{
	int	arr[5];
	int	cnt;

	sort_ascend(inp_list, inp_list_size, arr);
	cnt = 2;
	while (cnt)
	{
		if (stks->stk_a->value == arr[0] || stks->stk_a->value == arr[1])
		{
			ft_push(stks, PB);
			ft_printf("pb\n");
			cnt--;
		}
		else
		{
			ft_rotate(stks, RA);
			ft_printf("ra\n");
		}
	}
	sort_3args(stks->stk_a);
	if (stks->stk_b->value < stks->stk_b->next->value)
		ft_printf("sb\n");
	ft_printf("pa\npa\n");
}
