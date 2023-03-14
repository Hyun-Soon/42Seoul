#ifndef LIBFT_H
#define LIBFT_H
#include <stdlib.h>

void    bzero(void *s, size_t n);
int ft_isalnum(int c);
int ft_isalpha(int c);
int ft_isascii(int c);
int ft_isdigit(int c);
int ft_isprint(int c);
void *memcpy(void *restrict dst, const void *restrict src, size_t n);
void *memset(void *b, int c, size_t len);
size_t	strlen(const char *s);

#endif