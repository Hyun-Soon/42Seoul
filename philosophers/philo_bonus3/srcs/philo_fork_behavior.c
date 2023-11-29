/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_behavior.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:17:11 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/29 22:36:29 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
//TODO :: 죽는 시간 밀림 수정 -> thread
//void	exit_routine(t_bundle *bundle)
//{
//	struct timeval	s_now;
	
//	if (bundle->eat_cnt == bundle->number_of_times_for_each)
//		exit(0);
//	//printf("case 0\n"); //
//	sem_wait(bundle->t_print_semaphore);
//	gettimeofday(&s_now, NULL);
//	printf("%ld	%d died\n", get_timestamp(bundle, s_now), bundle->id + 1);
//	printf("case 1\n"); //
//	exit(1);
//}

void	print_get_forks(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;
	long			temp_timestamp;

	gettimeofday(&s_now, NULL);
	sem_wait(bundle->t_eat_time_sem);
	time_since_last_meal = get_time_since(bundle->s_eat_time, s_now);
	sem_post(bundle->t_eat_time_sem);
	sem_wait(bundle->t_personal_eat_cnt_sem);
	if (time_since_last_meal < bundle->time_to_die
		&& bundle->eat_cnt != bundle->number_of_times_for_each)
	{
		sem_post(bundle->t_personal_eat_cnt_sem);
		sem_wait(bundle->t_print_semaphore);
		temp_timestamp = get_timestamp(bundle, s_now);
		//printf("%ld	%d has taken a fork\n", temp_timestamp, bundle->id + 1);
		//printf("%ld	%d has taken a fork\n", temp_timestamp, bundle->id + 1);
		printf("%ld	%d has taken a fork\n%ld	%d has taken a fork\n",
			temp_timestamp, bundle->id + 1, temp_timestamp, bundle->id + 1);
		sem_post(bundle->t_print_semaphore);
	}
	else
		sem_post(bundle->t_personal_eat_cnt_sem);
	//else
	//	sem_post(bundle->t_eat_cnt_sem); =>이거 주석처리해도 돌아갈듯? 어차피 죽을 때는 안풀어도 될거같은데 => 풀어줘야 모리터링에서 끝내지
}

void	get_forks(t_bundle *bundle)
{
	sem_wait(bundle->t_semaphore);
	sem_wait(bundle->t_semaphore);
	print_get_forks(bundle);
}

//void	get_first_fork(t_bundle *bundle, int *dead_or_full)
//{
//	sem_wait(bundle->s_semaphore[0]);
//	print_get_fork(bundle, dead_or_full);
//}

//void	get_second_fork(t_bundle *bundle, int *dead_or_full)
//{
//	sem_wait(bundle->s_semaphore[1]);
//	print_get_fork(bundle, dead_or_full);
//}

