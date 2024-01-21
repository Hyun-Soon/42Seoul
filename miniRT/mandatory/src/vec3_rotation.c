/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:32:43 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/26 18:07:42 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_vec3	rotate_y(t_vec3 vec, double theta)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = vec.x;
	prev_y = vec.y;
	prev_z = vec.z;
	vec.x = prev_z * sin(theta) + prev_x * cos(theta);
	vec.y = prev_y;
	vec.z = prev_z * cos(theta) - prev_x * sin(theta);
	return (vec);
}

void	rotate_h(t_camera *cam, double theta)
{
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	if (vlength2(vcross(vunit(vplus(vmult(cam->normal, cos_theta), \
	vmult(cam->vertical, -sin_theta))), vec3(0, 1, 0))) < 0.01)
		return ;
	cam->normal = vunit(vplus(vmult(cam->normal, cos_theta), \
	vmult(cam->vertical, -sin_theta)));
	cam->vertical = vunit(vminus(vmult(cam->vertical, -cos_theta), \
	vmult(cam->normal, sin_theta)));
}
