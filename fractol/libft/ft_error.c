/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuim <hyuim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 18:32:57 by hyuim             #+#    #+#             */
/*   Updated: 2023/06/29 21:01:14 by hyuim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_error(const char *err_msg, int fd)
{
	write(fd, err_msg, ft_strlen(err_msg));
	write(fd, "\n", 1);
	exit(1);
}
