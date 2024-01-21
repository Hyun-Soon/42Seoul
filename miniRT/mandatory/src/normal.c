/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:27:56 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/27 09:58:32 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

void	set_face_normal(t_ray *r, t_hit_rec *rec)
{
	rec->front_face = vdot(r->dir, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = vmult(rec->normal, -1);
}
