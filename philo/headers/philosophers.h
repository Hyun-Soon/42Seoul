/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:43:02 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/24 13:37:39 by hyuim            ###   ########.fr       */
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
	int				id;
	struct timeval	s_eat_time;
	struct s_bundle	*bundle;
}				t_philo;

typedef struct s_bundle
{
	int				odd_flag;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_for_each;
	int				sb_dead_or_full;
	struct timeval	s_start;
	pthread_t		*threads;
	pthread_mutex_t	*fork_mutexes;
	pthread_mutex_t	*eat_time_mutexes;
	pthread_mutex_t	*eat_cnt_mutexes;
	pthread_mutex_t	sb_dead_or_full_mutex;
	int				*forks;
	int				*eating_count;
}				t_bundle;

int		ft_atoi(const char *str);
int		atoi_args(t_bundle *bundle, t_philo *philos, int argc, char **argv);
void	free_remains(t_bundle *bundle, t_philo *philos);
int		init_bundle(t_bundle *bundle, t_philo *philos, int argc, char **argv);
int		setting_table(t_bundle *bundle, t_philo *philos);
int		ft_atoi(const char *str);
void	print_die_msg(t_bundle *bundle, int dead);
void	philo_put_down_forks(t_philo *philo);
int		destroy_all_mutexes_and_all_free(t_bundle *bundle, t_philo *philos);
void	notice_all_philos_full(t_bundle *bundle);
void	count_eat(t_bundle *bundle, int *full_flag, int idx);
void	check_dead_or_full(t_bundle *bundle,
			t_philo *philos, int idx, int full_flag);
int		destroy_pre_fork_mutexes(t_bundle *bundle, t_philo *philos, int idx);
int		destroy_pre_fork_mutexes_and_eat_time_mutexes(t_bundle *bundle,
			t_philo *philos, int idx);
int		destroy_all_mutexes(t_bundle *bundle, t_philo *philos, int idx);
void	null_init(t_bundle *bundle);
t_philo	*init_philos(t_bundle *bundle);
int		malloc_bundle_members(t_bundle *bundle);
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	philo_thinking(t_philo *philo);
void	sleep_for_odd_philos(t_philo *philo);
void	*routine(void *ph);
void	get_left_fork(t_philo *philo);
void	get_right_fork(t_philo *philo);
void	put_down_left(t_philo *philo);
void	put_down_right(t_philo *philo);
void	philo_put_down_forks(t_philo *philo);
long	get_timestamp(t_philo *philo);
long	get_time_since(struct timeval s_before_time);
void	set_eat_time(t_philo *philo);
void	optimized_sleep(struct timeval ref_time, int target_time);
int		set_start_time(t_bundle *bundle, t_philo *philos);
void	all_pthreads_create(t_bundle *bundle, t_philo *philos, int idx);
void	all_pthreads_join(t_bundle *bundle, int idx);

#endif