/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:42:24 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/29 21:06:31 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	check_mandelbrot_set(double c_r, double c_i, t_mlx *mlx)
{
	int		n;
	double	temp;
	double	z_r;
	double	z_i;

	n = 0;
	z_r = 0;
	z_i = 0;
	while (n < mlx->n_limit && z_r * z_r + z_i * z_i < 4)
	{
		temp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2.0 * temp * z_i + c_i;
		n++;
	}
	return (n);
}

void	draw_mandelbrot(t_mlx *mlx, int x, int y)
{
	int		n;
	double	c_r;
	double	c_i;

	while (++y < HEIGHT)
	{
		c_i = mlx->max_i - (double)y * mlx->i_per_height;
		while (++x < WIDTH)
		{
			c_r = mlx->min_r + (double)x * mlx->r_per_width;
			n = check_mandelbrot_set(c_r, c_i, mlx);
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
