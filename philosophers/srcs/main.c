/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:45 by hyuim             #+#    #+#             */
/*   Updated: 2023/10/27 14:58:36 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]
#include "../headers/philosophers.h"
#include <stdio.h>

//free list : 1. philos 2. chopsticks 3. threads

void	*test(t_philo *philos)
{
	printf("%d\n", philos->id);
	return NULL;
}

int main(int argc, char**argv)
{
	t_bundle	bundle;
	struct timeval now;
	struct timeval start;
	int	idx;

	if (argc < 5)
	{
		write(2, "Not enough args.\n", 17);
		return (1);
	}

	if (atoi_args(&bundle, argc, argv) == -1)
	{
		free_remains();
		return (1);
	}

	idx = -1;
	while (++idx < bundle.num_of_philos)
		pthread_create(&bundle.threads[idx], NULL, test, (void *)&bundle.philos[idx]);

	idx = -1;
	while (++idx < bundle.num_of_philos)
		pthread_join(bundle.threads[idx], NULL);
	//printf("here\n");
	//int idx2 = -1;
	//printf("%d\n", bundle.num_of_philos);
	//while (++idx2 < bundle.num_of_philos)
	//	printf("%d\n", bundle.chopsticks[idx2]);


	//gettimeofday(&start, NULL);
	//gettimeofday(&now, NULL);
	//printf("%u\n", now.tv_usec - start.tv_usec);
	return (0);
}

int	setting_table(t_bundle *bundle)
{
	int	idx;
	bundle->threads = (pthread_t *)malloc(sizeof(pthread_t) * bundle->num_of_philos);
	if (!bundle->threads)
		return (-1);
	bundle->philos = (t_philo *)malloc(sizeof(t_philo) * bundle->num_of_philos);
	if (!bundle->philos)
		return (-1);
	bundle->chopsticks = (int *)malloc(sizeof(int) * bundle->num_of_philos);
	if (!bundle->chopsticks)
		return (-1);
	idx = -1;
	while (++idx < bundle->num_of_philos)
	{
		bundle->philos[idx].id = idx;
		bundle->philos[idx].left_chop = idx % bundle->num_of_philos;
		bundle->philos[idx].right_chop = (idx + 1) % bundle->num_of_philos;
		bundle->philos[idx].status = HUNGRY;
		bundle->chopsticks[idx] = 1;
	}
	return (0);
}

int	atoi_args(t_bundle *bundle, int argc, char **argv)
{
	bundle->num_of_philos = ft_atoi(argv[1]);
	bundle->time_to_die = ft_atoi(argv[2]);
	bundle->time_to_eat = ft_atoi(argv[3]);
	bundle->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		bundle->number_of_times_for_each = ft_atoi(argv[5]);
	else
		bundle->number_of_times_for_each = -1014;
	if (bundle->num_of_philos == -1
		|| bundle->number_of_times_for_each == -1
		|| bundle->time_to_die == -1
		|| bundle->time_to_eat == -1
		|| bundle->time_to_sleep == -1)
	{
		write(2, "arg err.\n", 9);
		return (-1);
	}
	else
	{
		if (setting_table(bundle) == -1)
			return (-1);
		return (0);
	}
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	ret;

	ret = 0;
	sign = 1;
	if (*str == 0)
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		ret = ret * 10 + (long)(*str - '0');
		if (ret < -2147483648 || ret > 2147483647)
			return (-1);
		str++;
	}
	ret = sign * ret;
	return (ret);
}
