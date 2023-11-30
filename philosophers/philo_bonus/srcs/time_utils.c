/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:22:49 by hyuim             #+#    #+#             */
/*   Updated: 2023/11/30 11:26:05 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

long	get_time_since(struct timeval s_before_time, struct timeval s_now)
{
	long			ret;

	ret = (s_now.tv_sec - s_before_time.tv_sec) * 1000
		+ (s_now.tv_usec / 1000) - (s_before_time.tv_usec / 1000);
	return (ret);
}

long	get_timestamp(t_bundle *bundle, struct timeval s_now)
{
	long			ret;

	ret = (s_now.tv_sec - bundle->s_start.tv_sec) * 1000
		+ (s_now.tv_usec / 1000) - (bundle->s_start.tv_usec / 1000);
	return (ret);
}

void	optimized_sleep(struct timeval ref_time, int target_time)
{
	long			sleep_time;
	long			u_constant_time;
	int				time_threadhold;
	struct timeval	s_now;

	u_constant_time = target_time * 1000
		+ ref_time.tv_sec * 1000000 + ref_time.tv_usec;
	time_threadhold = 4 * DT;
	gettimeofday(&s_now, NULL);
	sleep_time = u_constant_time - s_now.tv_sec * 1000000 - s_now.tv_usec;
	while (sleep_time > 0)
	{
		if (sleep_time > time_threadhold)
			usleep(sleep_time / 2);
		else
			usleep(DT);
		gettimeofday(&s_now, NULL);
		sleep_time = u_constant_time - s_now.tv_sec * 1000000 - s_now.tv_usec;
	}
}
