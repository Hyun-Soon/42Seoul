/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:00:34 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/26 17:43:30 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_hook.h"

void	move_camera(int keycode, t_param *par)
{
	if (keycode == KEY_E)
		par->scene.camera.orig = \
		vplus(par->scene.camera.orig, par->scene.camera.up);
	else if (keycode == KEY_Q)
		par->scene.camera.orig = \
		vminus(par->scene.camera.orig, par->scene.camera.up);
	else if (keycode == KEY_S)
		par->scene.camera.orig = \
		vminus(par->scene.camera.orig, par->scene.camera.forward);
	else if (keycode == KEY_A)
		par->scene.camera.orig = \
		vminus(par->scene.camera.orig, par->scene.camera.right);
	else if (keycode == KEY_D)
		par->scene.camera.orig = \
		vplus(par->scene.camera.orig, par->scene.camera.right);
	else if (keycode == KEY_W)
		par->scene.camera.orig = \
		vplus(par->scene.camera.orig, par->scene.camera.forward);
	camera(&par->scene.camera, par->scene.canvas.aspect_ratio);
	snapshot(par);
}

void	rotate_camera(int keycode, t_param *par)
{
	double	theta;

	theta = M_PI / 18;
	if (keycode == KEY_LEFT)
		par->scene.camera.normal = rotate_y(par->scene.camera.normal, theta);
	else if (keycode == KEY_RIGHT)
		par->scene.camera.normal = rotate_y(par->scene.camera.normal, -theta);
	else if (keycode == KEY_UP)
		rotate_h(&par->scene.camera, theta);
	else if (keycode == KEY_DOWN)
		rotate_h(&par->scene.camera, -theta);
	camera(&par->scene.camera, par->scene.canvas.aspect_ratio);
	snapshot(par);
}

t_bool	is_move_key(int keycode)
{
	if (KEY_Q <= keycode && keycode <= KEY_E)
		return (TRUE);
	if (KEY_A <= keycode && keycode <= KEY_D)
		return (TRUE);
	return (FALSE);
}

t_bool	is_rotate_key(int keycode)
{
	if (KEY_LEFT <= keycode && keycode <= KEY_UP)
		return (TRUE);
	return (FALSE);
}

int	key_hook(int keycode, t_param *par)
{
	if (keycode == 53)
	{
		mlx_destroy_window(par->mlx, par->win);
		exit(0);
	}
	else if (is_move_key(keycode))
		move_camera(keycode, par);
	else if (is_rotate_key(keycode))
		rotate_camera(keycode, par);
	return (0);
}
