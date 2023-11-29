/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:16:07 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/29 23:41:50 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

//void	wake_up_or_die(t_bundle *bundle, long time_left_to_die, struct timeval check_time, int target_time)
//{
//	struct timeval	s_now;

//	if (time_left_to_die < target_time)
//	{
//		optimized_sleep(check_time, time_left_to_die);
//		//printf("time left to die : %ld\n", time_left_to_die);
//		sem_wait(bundle->t_print_semaphore);
//		gettimeofday(&s_now, NULL);
//		printf("%ld	%d died\n", get_timestamp(bundle, s_now), bundle->id + 1);
//		//printf("case 2\n");
//		exit(1);
//	}
//	optimized_sleep(check_time, target_time);
//}

void	philo_eating(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;
	//long	m		time_left_to_die;

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
		printf("%ld	%d is eating\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->t_print_semaphore);
		sem_wait(bundle->t_personal_eat_cnt_sem);
		bundle->eat_cnt++;
		sem_post(bundle->t_personal_eat_cnt_sem);
		bundle->s_eat_time = s_now; //CHECK :: 이거 함수 나가면 s_now변수 사라져서 s_eat_time에 문제 생기나? -> 아닐듯?
	}
	else
		sem_post(bundle->t_personal_eat_cnt_sem);

	optimized_sleep(s_now, bundle->time_to_eat);

	sem_post(bundle->t_semaphore);
	sem_post(bundle->t_semaphore);
}

void	philo_sleeping(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;

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
		printf("%ld	%d is sleeping\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->t_print_semaphore);
	}
	else
		sem_post(bundle->t_personal_eat_cnt_sem);
	//else
	//	exit_routine(bundle);

	//CHECK :: 여기서 s_now를 새로 업데이트 해줘야할까? 실험해보는게 빠를듯
	optimized_sleep(s_now, bundle->time_to_sleep);
}

void	philo_thinking(t_bundle *bundle)
{
	struct timeval	s_now;
	long			time_since_last_meal;

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
		printf("%ld	%d is thinking\n",
			get_timestamp(bundle, s_now), bundle->id + 1);
		sem_post(bundle->t_print_semaphore);
	}
	else
		sem_post(bundle->t_personal_eat_cnt_sem);
	//else
	//	exit_routine(bundle);
	if (bundle->odd_flag)
		usleep(DT << 1);
}

void	close_sems(t_bundle *bundle)
{
	if (sem_close(bundle->t_eat_time_sem) == -1)
		exit(51);
	if (sem_close(bundle->t_personal_eat_cnt_sem) == -1)
		exit(52);
}

void	*monitoring(void *bd)
{
	t_bundle *bundle;
	struct timeval	s_now;

	bundle = (t_bundle *)bd;
	//printf("%d's thread\n", bundle->id + 1);
	//printf("after thread, s_start usec : %d\n", bundle->s_start.tv_usec);
	while(1)
	{
		gettimeofday(&s_now, NULL);
		sem_wait(bundle->t_eat_time_sem);
		if (get_time_since(bundle->s_eat_time, s_now) >= bundle->time_to_die) //공유 변수
		{
			//sem_post(bundle->t_eat_time_sem); //어차피 이프로세스만 쓰기 때문에  post 안해줘도 됌.
			sem_wait(bundle->t_print_semaphore);
			gettimeofday(&s_now, NULL);
			//printf("get time since : %ld\n", get_time_since(bundle->s_eat_time, s_now));
			printf("%ld	%d died\n", get_timestamp(bundle, s_now), bundle->id + 1);
			close_sems(bundle);
			exit(1);
		}
		sem_post(bundle->t_eat_time_sem);
		//sem_wait(bundle->t_eat_cnt_sem);
		sem_wait(bundle->t_personal_eat_cnt_sem);
		if (bundle->eat_cnt == bundle->number_of_times_for_each) //공유 변수
		{
			printf("%d is full | cnt : %d\n", bundle->id + 1, bundle->eat_cnt);
			sem_post(bundle->t_eat_cnt_sem);

			//---------------------------------------------
			//TODO :: 1129
			//여기서 포크가 4개로 복사되진 않을까?
			//복사되지 않으려면 thinking에서 여기로 들어오면 안돼.

			//sem open 할 때 3개를 만들어줬어도, sem post로 4, 5 그 이상의 값을 만들 수 있음 => 문제생김 (test/test.c 확인)
			//내 status가 EATING일 때(semaphore lock 보장해줘야 함)만 post 2번 한다면?
			//sem_post(bundle->t_semaphore);
			//sem_post(bundle->t_semaphore);
			//---------------------------------------------

			
			close_sems(bundle);
			exit(0);
		}
		sem_post(bundle->t_personal_eat_cnt_sem);
		//sem_wait(bundle->t_eat_cnt_sem);
		usleep(DT);
	}
	exit(2);
}
//TODO :: 공유변수 : s_eat_time, eat_cnt

int	survival(t_bundle *bundle)
{
	pthread_t		thread;
	//TODO :: from here
	//printf("after fork, s_start usec : %d\n", bundle->s_start.tv_usec);
	pthread_create(&thread, NULL, monitoring, (void *)bundle);
	//finish_flag = 0;
	if (bundle->id % 2 == 1)
		optimized_sleep(bundle->s_start, bundle->time_to_die / 4);
	while (1)
	{
		get_forks(bundle);
		philo_eating(bundle);
		philo_sleeping(bundle);
		philo_thinking(bundle);
	}
	exit(3);
}
