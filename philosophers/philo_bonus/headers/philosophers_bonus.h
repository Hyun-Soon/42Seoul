/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:27 by hyuim             #+#    #+#             */
/*   Updated: 2023/12/03 13:10:50 by hyuim            ###   ########.fr       */
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
	int				hold_forks;
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_for_each;
	int				eat_cnt;
	int				time_to_eat_minus_one;
	char			*sem_name;
	sem_t			*t_semaphore;
	char			*print_sem_name;
	sem_t			*t_print_semaphore;
	char			**eat_time_sem_name;
	sem_t			*t_eat_time_sem;
	char			**personal_eat_cnt_name;
	sem_t			*t_personal_eat_cnt_sem;
	char			*eat_cnt_sem_name;
	sem_t			*t_eat_cnt_sem;
	struct timeval	s_start;
	struct timeval	s_eat_time;
}				t_bundle;

int		ft_atoi(const char *str);
int		make_semaphores(t_bundle *bundle);
int		ft_atoi(const char *str);
void	make_philosophers(t_bundle *bundle);
void	wait_philosophers(t_bundle *bundle);
void	delete_semaphores(t_bundle *bundle);
void	free_remains(t_bundle *bundle);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
int		survival(t_bundle *bundle);
long	get_time_since(struct timeval s_before_time, struct timeval s_now);
long	get_timestamp(t_bundle *bundle, struct timeval s_now);
void	optimized_sleep(struct timeval ref_time, int target_time);
void	print_get_fork(t_bundle *bundle);
void	get_forks(t_bundle *bundle);
void	exit_routine(t_bundle *bundle);
char	*ft_chardup(int c);
sem_t	*make_sem_until_success(char *name, int s);
void	up_hold_forks(t_bundle *bundle);
void	down_hold_forks(t_bundle *bundle);
void	exit_full(t_bundle *bundle);
void	exit_starve(t_bundle *bundle, struct timeval s_now);
void	return_forks(t_bundle *bundle);
void	*monitoring(void *bd);
void	close_sems(t_bundle *bundle);
char	*name_eat_sems(int idx, int noise);
void	malloc_2d_sem_names(t_bundle *bundle);
void	print_eating(t_bundle *bundle, struct timeval s_now);

#endif