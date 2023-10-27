/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:02 by hyuim             #+#    #+#             */
/*   Updated: 2023/10/27 14:48:57 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define HUNGRY 0
# define EATING 1
# define SLEEPING 2
# define THINGKING 3

typedef struct s_bundle
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_for_each;
	pthread_t	*threads;
	t_philo		*philos;
	unsigned int	*chopsticks;
}				t_bundle;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	*left_chop;
	unsigned int	*right_chop;
	unsigned int	status;
}				t_philo;

int	ft_atoi(const char *str);
int	atoi_args(t_bundle *bundle, int argc, char **argv);


#endif