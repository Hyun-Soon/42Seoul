/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusekim <yusekim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:47:20 by dongseo           #+#    #+#             */
/*   Updated: 2023/12/26 17:43:54 by yusekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "mlx.h"
# include "trace.h"

void	snapshot(t_param *par);
int		convert_color3_int(t_color3 pixel_color);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif
