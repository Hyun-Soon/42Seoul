/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:20:43 by hyuim             #+#    #+#             */
/*   Updated: 2023/07/01 17:13:01 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# define WIDTH 1000
# define HEIGHT 1000
# define ZOOMIN 0.9
# define ZOOMOUT 1.1
# define XBUTTON 17
# define COLOR_NOISE 10
# define INIT_ERROR_MSG "MLX init error\n"
# define INPUT_ERROR_MSG "Wrong input error.\n\
Fractal list [mandelbrot, julia, burning ship]\n"
# define MANDELBROT "mandelbrot"
# define JULIA "julia"

# include <unistd.h>
# include "mlx.h"
# include <math.h>
# include "../libft/libft.h"

typedef struct s_fractal
{
	int		type;
	double	c_r;
	double	c_i;
}				t_fractal;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			n_limit;
	int			color1;
	int			color2;
	int			color3;
	int			cc_count;
	double		move_const;
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
	double		r_per_width;
	double		i_per_height;
	t_img		img;
	t_fractal	fractal;
}				t_mlx;

void	(*draw_fractal)(t_mlx *mlx, int x, int y);
void	ft_error(const char *err_msg, int fd);
int		check_input(int argc, char *argv[], t_mlx *mlx);
int		init_mlx(t_mlx *mlx);
void	draw_mandelbrot(t_mlx *mlx, int x, int y);
int		check_julia_set(double z_r, double z_i, t_mlx *mlx);
void	draw_julia(t_mlx *mlx, int x, int y);
void	draw_burning_ship(t_mlx *mlx, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		check_mandelbrot_set(double c_r, double c_i, t_mlx *mlx);
int		check_burning_ship_set(double c_r, double c_i, t_mlx *mlx);
int		key_hook(int keycode, t_mlx *mlx);
int		mouse_hook(int mouse_button, int x, int y, t_mlx *mlx);
void	zoomin(t_mlx *mlx, int x, int y);
void	zoomout(t_mlx *mlx, int x, int y);
void	move_fractal(int keycode, t_mlx *mlx);
void	move_left(t_mlx *mlx);
void	move_right(t_mlx *mlx);
void	move_up(t_mlx *mlx);
void	move_down(t_mlx *mlx);
void	color_change(t_mlx *mlx);
void	init_color(t_mlx *mlx);
int		close_window(t_mlx *mlx);

#endif