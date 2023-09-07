/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:36:28 by hyuim             #+#    #+#             */
/*   Updated: 2023/09/07 17:12:58 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define ERROR "Error\n"
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	int				content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct	s_dll
{
	int				value;
	struct s_dll	*next;
	struct s_dll	*prev;
}				t_dll;

typedef struct	s_stacks
{
	t_dll		*stk_a;
	t_dll		*stk_b;
	t_list		*cmd_list;
}				t_stacks;

void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char *str, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);


t_list	*ft_lstnew(int content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_stacks *stks, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(int));
void	ft_lstclear(t_list **lst, void (*del)(int));
void	ft_lstiter(t_list *lst, void (*f)(int));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		is_percent(char c);
int		is_back_slash(char c);
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
int		read_format(const char *format, va_list ap);
size_t	ft_strlen(const char *s);
void	ft_error(const char *err_msg, int fd);
double	fractol_atodb(const char *str);
int		ft_strcmp(const char *str1, const char *str2);
void	*ft_realloc(int org_size, void *org_ptr, int new_size);
int		ft_printf(const char *format, ...);
int		read_format(const char *format, va_list ap);

#endif
