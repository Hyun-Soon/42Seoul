/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:42:11 by dongseo           #+#    #+#             */
/*   Updated: 2024/01/03 10:37:05 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "scene.h"
#include "map_parse.h"

void	parse_ambient(char **line, t_scene *scene)
{
	if (get_split_cnt(line) != 3)
		ft_perror("Wrong input err");
	scene->amb_ratio = get_ratio(line[1]);
	scene->ambient = vmult(get_color(line[2]), scene->amb_ratio);
}

void	parse_camera(char **line, t_scene *scene)
{
	double		fov;

	if (get_split_cnt(line) != 4)
		ft_perror("Wrong input err");
	scene->camera.orig = get_tuple(line[1]);
	scene->camera.normal = get_normal(line[2]);
	fov = atodb(line[3]);
	if (fov < 0 || fov > 180)
		ft_perror("Wrong input err");
	scene->camera.fov = fov;
	camera(&scene->camera, scene->canvas.aspect_ratio);
}

void	parse_light(char **line, t_scene *scene)
{
	t_point3	point;
	double		ratio;
	t_color3	color;

	if (get_split_cnt(line) != 4)
		ft_perror("Wrong input err");
	point = get_tuple(line[1]);
	ratio = get_ratio(line[2]);
	color = get_color(line[3]);
	oadd(&scene->light, object(LIGHT_POINT, \
	light_point(point, ratio, color), color3(0, 0, 0)));
}

t_light	*light_point(t_point3 l_origin, double b_ratio, t_color3 l_color)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->origin = l_origin;
	light->light_color = l_color;
	light->bright_ratio = b_ratio;
	return (light);
}

void	camera(t_camera *cam, double aspect_ratio)
{
	cam->viewport_w = 2.0;
	cam->viewport_h = cam->viewport_w / aspect_ratio;
	cam->focal_len = 1 / tan((cam->fov / 360 * M_PI));
	cam->horizontal = vmult(vunit(vcross(cam->normal, vec3(0, 1, 0))), 2.0);
	cam->vertical = \
	vmult(vunit(vcross(cam->horizontal, cam->normal)), -cam->viewport_h);
	cam->l_top = vplus(vminus(vminus(cam->orig, vdivide(cam->horizontal, 2)), \
	vdivide(cam->vertical, 2)), vmult(cam->normal, cam->focal_len));
	cam->up = vec3(0, 1, 0);
	cam->forward = vunit(vec3(cam->normal.x, 0, cam->normal.z));
	cam->right = vunit(cam->horizontal);
}
