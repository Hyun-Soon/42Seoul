/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:40:24 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/01 17:13:45 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_fractal(int keycode, t_mlx *mlx)
{
	if (keycode == 123)
		move_left(mlx);
	else if (keycode == 124)
		move_right(mlx);
	else if (keycode == 125)
		move_down(mlx);
	else
		move_up(mlx);
	return ;
}

void	move_left(t_mlx *mlx)
{
	mlx->min_r -= 0.1 * mlx->move_const;
	draw_fractal(mlx, -1, -1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return ;
}

void	move_right(t_mlx *mlx)
{
	mlx->min_r += 0.1 * mlx->move_const;
	draw_fractal(mlx, -1, -1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return ;
}

void	move_up(t_mlx *mlx)
{
	mlx->max_i += 0.1 * mlx->move_const;
	draw_fractal(mlx, -1, -1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return ;
}

void	move_down(t_mlx *mlx)
{
	mlx->max_i -= 0.1 * mlx->move_const;
	draw_fractal(mlx, -1, -1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	return ;
}
