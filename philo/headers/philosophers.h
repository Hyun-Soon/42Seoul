/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:02 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/23 21:20:24 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

# define DT 200

typedef struct s_philo
{
	int	id;
	struct timeval	s_eat_time;
	struct s_bundle	*bundle;
}				t_philo;

typedef struct s_bundle
{
	int	odd_flag;
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_for_each;
	int	sb_dead_or_full;
	struct timeval s_start;
	pthread_t	*threads;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	*eat_time_mutexes;
	pthread_mutex_t	*eat_cnt_mutexes;
	pthread_mutex_t	sb_dead_or_full_mutex;
	int	*forks;
	int	*eating_count;
}				t_bundle;

int	ft_atoi(const char *str);
int	atoi_args(t_bundle *bundle, t_philo *philos, int argc, char **argv);
void	free_remains(t_bundle *bundle, t_philo *philos);
int	init_bundle(t_bundle *bundle, t_philo *philos, int argc, char **argv);
int	setting_table(t_bundle *bundle, t_philo *philos);
int	ft_atoi(const char *str);
void	print_die_msg(t_bundle *bundle, int dead);
void	philo_put_down_forks(t_philo *philo);
void	destroy_all_mutexes_and_all_free(t_bundle *bundle, t_philo *philos);




#endif