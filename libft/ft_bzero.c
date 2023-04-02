/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:22:26 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/21 15:42:34 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	bzero(void *s, size_t n)
{
	unsigned int	*temp;

	temp = (unsigned int *)s;
	while (n--)
	{	
		*temp = 0;
		temp++;
	}
	return ;
}