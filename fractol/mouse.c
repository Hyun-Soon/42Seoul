/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 14:39:13 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/29 20:56:43 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int mouse_button, int x, int y, t_mlx *mlx)
{
	if (mouse_button == 4)
		zoomin(mlx, x, y);
	else if (mouse_button == 5)
		zoomout(mlx, x, y);
	return (0);
}
