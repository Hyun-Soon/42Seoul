/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongseo <dongseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:55:29 by yusekim           #+#    #+#             */
/*   Updated: 2024/01/03 10:39:36 by dongseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "map_parse.h"

t_color3	get_color(char *line)
{
	char		**colors;
	t_color3	ret;
	int			temp[3];
	int			i;

	colors = ft_split(line, ',');
	if (get_split_cnt(colors) != 3)
		ft_perror("Wrong input err");
	i = -1;
	while (++i < 3)
	{
		temp[i] = rt_ft_atoi(colors[i]);
		if (temp[i] < 0 || temp[i] > 256)
			ft_perror("Wrong input err");
	}
	ret = vdivide(color3((double)temp[0], \
	(double)temp[1], (double)temp[2]), 255.0);
	split_free(colors);
	return (ret);
}

t_vec3	get_tuple(char *line)
{
	char	**vec;
	t_vec3	ret;
	double	temp[3];
	int		i;

	vec = ft_split(line, ',');
	if (get_split_cnt(vec) != 3)
		ft_perror("Wrong input err");
	i = -1;
	while (++i < 3)
		temp[i] = atodb(vec[i]);
	ret = vec3(temp[0], temp[1], temp[2]);
	split_free(vec);
	return (ret);
}

double	get_ratio(char *line)
{
	double	ratio;

	ratio = atodb(line);
	if (ratio < 0 || ratio > 1)
		ft_perror("Wrong input err");
	return (ratio);
}

t_vec3	get_normal(char *line)
{
	t_vec3	temp;

	temp = get_tuple(line);
	if (temp.x < -1 || temp.x > 1 || \
	temp.y < -1 || temp.y > 1 || \
	temp.z < -1 || temp.z > 1)
		ft_perror("Wrong input err");
	return (vunit(temp));
}
