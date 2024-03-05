/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:25:55 by yusekim           #+#    #+#             */
/*   Updated: 2023/12/27 11:29:37 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	convert_color3_int(t_color3 pixel_color)
{
	int		color;

	color = 256 * 256 * (int)(255.999 * pixel_color.x) + \
	256 * (int)(255.999 * pixel_color.y) + (int)(255.999 * pixel_color.z);
	return (color);
}

void	snapshot(t_param *par)
{
	int			i;
	int			j;
	double		u;
	double		v;
	t_color3	pixel_color;

	j = -1;
	while (++j < par->scene.canvas.height)
	{
		i = -1;
		while (++i < par->scene.canvas.width)
		{
			u = (double)i / (par->scene.canvas.width - 1);
			v = (double)j / (par->scene.canvas.height - 1);
			par->scene.ray = ray_primary(&par->scene.camera, u, v);
			pixel_color = ray_color(&par->scene);
			my_mlx_pixel_put(&par->img, i, j, convert_color3_int(pixel_color));
		}
	}
	mlx_put_image_to_window(par->mlx, par->win, par->img.img, 0, 0);
}
