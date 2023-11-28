/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:27 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/28 16:15:10 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <signal.h>

# define DT 200

typedef struct s_bundle
{
	int				id;
	int				odd_flag;
	int				dead_flag; //
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_for_each;
	int				eat_cnt;
	char			**sem_name;
	sem_t			**s_semaphore;
	sem_t			*s_print_semaphore;
	pthread_t		thread;
	struct timeval	s_start;
	struct timeval	s_dead_time; //
	struct timeval	s_eat_time;
}				t_bundle;

int		ft_atoi(const char *str);
int		make_semaphore(t_bundle *bundle);
int		ft_atoi(const char *str);
void	make_philosophers(t_bundle *bundle);
void	wait_philosophers(t_bundle *bundle);
void	delete_semaphores(t_bundle *bundle);
void	free_remains(t_bundle *bundle);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		routine(t_bundle *bundle);
long	get_time_since(struct timeval s_before_time, struct timeval s_now);
long	get_timestamp(t_bundle *bundle, struct timeval s_now);
void	optimized_sleep(struct timeval ref_time, int target_time);
void	print_get_fork(t_bundle *bundle, int *dead_or_full);
void	get_first_fork(t_bundle *bundle, int *dead_or_full);
void	get_second_fork(t_bundle *bundle, int *dead_or_full);

#endif