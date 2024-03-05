/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:16:49 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/27 10:10:32 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool	hit_pl(t_plane *pl, t_ray *ray, t_hit_rec *rec, t_color3 albedo)
{
	double	t;

	t = vdot(vminus(pl->point, ray->orig), pl->normal) / \
	vdot(pl->normal, ray->dir);
	if (t < rec->tmin || rec->tmax < t)
		return (FALSE);
	rec->t = t;
	rec->p = ray_at(ray, t);
	rec->normal = pl->normal;
	set_face_normal(ray, rec);
	rec->albedo = albedo;
	return (TRUE);
}
