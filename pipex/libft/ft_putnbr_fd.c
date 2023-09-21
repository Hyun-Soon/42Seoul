/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:27:42 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/06 15:11:06 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbr_recur(int n, int fd, int sign);

void	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		sign = -1;
		write(fd, "-", 1);
	}
	ft_nbr_recur(n, fd, sign);
	return ;
}

static void	ft_nbr_recur(int n, int fd, int sign)
{
	char	c;

	if (n / 10 != 0)
		ft_nbr_recur(n / 10, fd, sign);
	c = sign * (n % 10) + '0';
	write(fd, &c, 1);
}
