/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:27 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/29 23:35:26 by hyuim            ###   ########.fr       */
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
	int				id;//y
	int				odd_flag;//y
	int				num_of_philos; //y
	int				time_to_die; //y
	int				time_to_eat; //y
	int				time_to_sleep;//y
	int				number_of_times_for_each;//y
	int				eat_cnt;//y

	char			*sem_name;//y
	sem_t			*t_semaphore;// literal fork

	char			*print_sem_name;//y
	sem_t			*t_print_semaphore;//y

	char			**eat_time_sem_name;//new
	sem_t			*t_eat_time_sem;//make after fork

	char			**personal_eat_cnt_name;
	sem_t			*t_personal_eat_cnt_sem;//make after fork

	char			*eat_cnt_sem_name;//new
	sem_t			*t_eat_cnt_sem;// for 5th arg
	
	struct timeval	s_start;//y
	struct timeval	s_eat_time;//y
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
void	print_get_forks(t_bundle *bundle);
void	get_forks(t_bundle *bundle);
void	exit_routine(t_bundle *bundle);
char	*ft_chardup(int c);
sem_t	*make_sem_until_success(char *name, int s);

#endif