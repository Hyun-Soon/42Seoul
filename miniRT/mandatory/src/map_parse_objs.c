/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_objs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 17:48:53 by yusekim           #+#    #+#             */
/*   Updated: 2024/01/03 10:36:53 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "scene.h"
#include "map_parse.h"

double	get_uvalue(char *line)
{
	double	diameter;

	diameter = atodb(line);
	if (diameter <= 0)
		ft_perror("Wrong input err");
	return (diameter);
}

void	parse_sphere(char **line, t_scene *scene)
{
	double		radius;
	t_point3	point;
	t_color3	color;

	if (get_split_cnt(line) != 4)
		ft_perror("Wrong input err");
	point = get_tuple(line[1]);
	radius = get_uvalue(line[2]) / 2;
	color = get_color(line[3]);
	oadd(&scene->world, object(SP, sphere(point, radius), color));
}

void	parse_cylinder(char **line, t_scene *scene)
{
	double		radius;
	double		height;
	t_point3	point;
	t_color3	color;
	t_vec3		normal;

	if (get_split_cnt(line) != 6)
		ft_perror("Wrong input err");
	point = get_tuple(line[1]);
	normal = get_normal(line[2]);
	radius = get_uvalue(line[3]) / 2;
	height = get_uvalue(line[4]);
	color = get_color(line[5]);
	oadd(&scene->world, object(CY, \
	cylinder(point, normal, height, radius), color));
	point = vplus(point, vmult(normal, height / 2));
	oadd(&scene->world, object(DK, disk(point, normal, radius), color));
	point = vplus(point, vmult(normal, -height));
	oadd(&scene->world, object(DK, disk(point, normal, radius), color));
}

void	parse_plane(char **line, t_scene *scene)
{
	t_point3	point;
	t_color3	color;
	t_vec3		normal;

	if (get_split_cnt(line) != 4)
		ft_perror("Wrong input err");
	point = get_tuple(line[1]);
	normal = get_normal(line[2]);
	color = get_color(line[3]);
	oadd(&scene->world, object(PL, plane(point, normal), color));
}
