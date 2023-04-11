/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:10:32 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/10 19:45:36 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		read_format(const char *format, va_list ap);
int		is_percent(char c);
int		check_conversion(char c);
int		print_conversion(char c, va_list ap);
int		print_c(va_list ap);
int		print_s(va_list ap);
int		print_p(va_list ap);
char	*ltoa_base(int base, unsigned long n);
int		print_d(va_list ap);
int		print_u(va_list ap);
int		print_x(va_list ap);
int		print_X(va_list ap);
int		print_percent(void);

#endif
