/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 20:36:46 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/01 17:15:26 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (!check_input(argc, argv, &mlx))
		ft_error(INPUT_ERROR_MSG, 2);
	if (!init_mlx(&mlx))
		ft_error(INIT_ERROR_MSG, 2);
	draw_fractal(&mlx, -1, -1);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_hook(mlx.win, XBUTTON, 0, close_window, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

int	check_input(int argc, char *argv[], t_mlx *mlx)
{
	if (argc == 2 && !ft_strcmp(MANDELBROT, argv[1]))
	{
		draw_fractal = &draw_mandelbrot;
		return (1);
	}
	else if (argc == 4 && !ft_strcmp(JULIA, argv[1]))
	{
		draw_fractal = &draw_julia;
		mlx->fractal.c_r = fractol_atodb(argv[2]);
		mlx->fractal.c_i = fractol_atodb(argv[3]);
		return (1);
	}
	else if (argc == 3 && !ft_strcmp("burning", argv[1])
		&& !ft_strcmp("ship", argv[2]))
	{
		draw_fractal = &draw_burning_ship;
		return (1);
	}
	return (0);
}

void	ft_error(const char *err_msg, int fd)
{
	write(fd, err_msg, ft_strlen(err_msg));
	write(fd, "\n", 1);
	exit(1);
}
