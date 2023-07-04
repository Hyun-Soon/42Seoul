/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:41:01 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/01 17:14:02 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	zoomin(t_mlx *mlx, int x, int y)
{
	mlx->min_r += x * mlx->r_per_width * 0.1;
	mlx->max_i -= y * mlx->i_per_height * 0.1;
	mlx->r_per_width *= ZOOMIN;
	mlx->i_per_height *= ZOOMIN;
	mlx->n_limit++;
	mlx->move_const /= 1.1;
	draw_fractal(mlx, -1, -1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return ;
}

void	zoomout(t_mlx *mlx, int x, int y)
{
	mlx->min_r -= x * mlx->r_per_width * 0.1;
	mlx->max_i += y * mlx->i_per_height * 0.1;
	mlx->r_per_width *= ZOOMOUT;
	mlx->i_per_height *= ZOOMOUT;
	mlx->n_limit--;
	mlx->move_const *= 1.1;
	draw_fractal(mlx, -1, -1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return ;
}
