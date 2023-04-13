/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:10:32 by hyuim             #+#    #+#             */
/*   Updated: 2023/04/12 13:39:24 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		read_format(const char *format, va_list ap);
size_t	ft_strlen(const char *s);
int		is_percent(char c);
int		check_conversion(char c);
int		print_conversion(char c, va_list ap, size_t *bytes);
int		print_c(va_list ap, size_t *bytes);
int		print_s(va_list ap, size_t *bytes);
int		print_p(va_list ap, size_t *bytes);
char	*ltoa_base(int base, unsigned long n);
int		print_d(va_list ap, size_t *bytes);
int		print_u(va_list ap, size_t *bytes);
int		print_x(va_list ap, size_t *bytes);
int		print_large_x(va_list ap, size_t *bytes);
int		print_percent(size_t *bytes);

#endif
