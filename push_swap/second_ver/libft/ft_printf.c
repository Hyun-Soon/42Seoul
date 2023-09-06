/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:45:47 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/01 14:51:10 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	size_t	bytes;

	va_start(ap, format);
	bytes = read_format(format, ap);
	va_end(ap);
	return (bytes);
}

// #include <stdio.h>
// #include <limits.h>
// int main()
// {
// 	int a, b;
// 	a = printf("%s\n", (char *)NULL);
// 	b = ft_printf("%s\n", (char *)NULL);
// 	printf("printf : %d, ft_printf : %d\n\n", a, b);
// 	return 0;
// }

	// printf("%lu\n", (long)INT_MAX);
	// printf("%ld\n", (long)INT_MIN);
	// printf("%lu\n", (long)INT_MIN);
	// printf("->> %lu\n", (long)(INT_MIN));
	// printf("%lu\n", (long)1);
	// printf("%lu\n", (unsigned long)1);
	// printf("%ld\n", (long)(-1));
	// printf("%ld\n", (unsigned long)(-1));
	// printf("%lu\n", ULONG_MAX);
	// printf("%lu\n", LONG_MIN);
	// printf("size of int : %lu\n", sizeof(int));
	// printf("size of long : %lu\n", sizeof(long));
/*
1. format읽기
2. '%' 구분하기
	2-1. '%' 아아니니면 그그대대로  출출력력하하기기
	2-2. '%'면  자자료료형형(d, s, c, ...)들어올 때 까지 해석하기
		(X) 2-2-1. % 바로 다음에 플래그(-0.# +)가 오는지 확인하기
		2-2-2. 플래그 아니고 숫자면 출력자릿수 만들기
			2-2-2-1. 숫자가 출력가능범위 밖인지 확인하기

*** "abcd%"인 경우 (%가 마지막) -> 생각하자.
*/
