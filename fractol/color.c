/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:37:05 by hyuim             #+#    #+#             */
/*   Updated: 2024/01/21 19:46:45 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	color_change(t_mlx *mlx)
{
	mlx->color1 <<= 1;
	mlx->color2 <<= 1;
	mlx->color3 <<= 1;
	mlx->cc_count++;
	if (mlx->cc_count == 10)
		init_color(mlx);
	draw_fractal(mlx, -1, -1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

void	init_color(t_mlx *mlx)
{
	mlx->cc_count = 0;
	mlx->color1 = 0x00111133;
	mlx->color2 = 0x00336666;
	mlx->color3 = 0x00991129;
}
