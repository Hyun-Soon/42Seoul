#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
		sign *= (44 - *str++);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
		if (res > LONG_MAX)
		{
			if (sign == 1)
				return ((int)LONG_MAX);
			else
				return ((int)LONG_MIN);
		}
	}
	return (sign * res);
}

#include <stdio.h>

int main(void)
{
	char *inp1 = "-9223372036854775807";
	char *inp2 = "9223372036854775806";
	printf("%d\n", atoi(inp1));
	printf("%d\n", atoi(inp2));
	printf("%d\n", ft_atoi(inp1));
	printf("%d\n", ft_atoi(inp2));
}
