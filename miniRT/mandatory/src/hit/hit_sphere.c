/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 19:17:38 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/27 11:01:18 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

double	sp_discriminant(t_ray *ray, t_sphere *sp, double *a, double *half_b);

t_bool	hit_sp(t_sphere *sp, t_ray *ray, t_hit_rec *rec, t_color3 albedo)
{
	double		discriminant;
	double		sqrtd;
	double		root;
	double		a;
	double		half_b;

	discriminant = sp_discriminant(ray, sp, &a, &half_b);
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || root > rec->tmax)
			return (FALSE);
	}
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = vdivide(vminus(rec->p, sp->center), sp->radius);
	set_face_normal(ray, rec);
	rec->albedo = albedo;
	return (TRUE);
}

double	sp_discriminant(t_ray *ray, t_sphere *sp, double *a, double *half_b)
{
	t_vec3		oc;
	double		c;

	oc = vminus(ray->orig, sp->center);
	*a = vlength2(ray->dir);
	*half_b = vdot(oc, ray->dir);
	c = vlength2(oc) - sp->radius2;
	return ((*half_b) * (*half_b) - *a * c);
}
