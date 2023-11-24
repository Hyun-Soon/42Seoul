/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:05:27 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/24 23:03:46 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define DT 200

typedef struct	s_bundle
{
	int	id;
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_for_each;
	int	eat_cnt;
	char		*sem_name;
	sem_t		s_semaphore;
	pthread_t	thread;
	struct timeval	s_start;
	struct timeval	s_eat_time;
}				t_bundle;
