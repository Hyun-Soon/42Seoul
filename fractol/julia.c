/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:43:21 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/29 21:06:12 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	check_julia_set(double z_r, double z_i, t_mlx *mlx)
{
	int		n;
	double	temp;

	n = 0;
	while (n < mlx->n_limit && z_r * z_r + z_i * z_i < 4)
	{
		temp = z_r;
		z_r = z_r * z_r - z_i * z_i + mlx->fractal.c_r;
		z_i = 2 * temp * z_i + mlx->fractal.c_i;
		n++;
	}
	return (n);
}

void	draw_julia(t_mlx *mlx, int x, int y)
{
	int		n;
	double	z_r;
	double	z_i;

	while (++y < HEIGHT)
	{
		z_i = mlx->max_i - (double)y * mlx->i_per_height;
		while (++x < WIDTH)
		{
			z_r = mlx->min_r + (double)x * mlx->r_per_width;
			n = check_julia_set(z_r, z_i, mlx);
			if (n == mlx->n_limit)
				my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
			else if (n < 33)
				my_mlx_pixel_put(&mlx->img, x, y,
					mlx->color1 + n * COLOR_NOISE);
			else if (n < 66)
				my_mlx_pixel_put(&mlx->img, x, y,
					mlx->color2 + n * COLOR_NOISE);
			else
				my_mlx_pixel_put(&mlx->img, x, y,
					mlx->color3 + n * COLOR_NOISE);
		}
		x = -1;
	}
}
