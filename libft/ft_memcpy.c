/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:24:56 by hyuim             #+#    #+#             */
/*   Updated: 2023/03/14 19:25:46 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    *memcpy(void *restrict dst, const void *restrict src, size_t n)
{
    void *dst1;
    void *src1;

    if (*dst == *src)
        return dst;

    *dst1 = dst;
    *src1 = src;

    return dst;    
}