/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:19:14 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 18:06:49 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put_floor(t_cub3d *data, int x, int y, int *color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	*(int *)dst = (color[0] << 16) + (color[1] << 8) + color[2];
}

void	put_color(t_cub3d *data, int x, int y, int color)
{
	int	x_max;
	int	y_max;
	int	tmp;
	int	p;

	tmp = x;
	p = y;
	x_max = x;
	y_max = y;
	while (y < y_max)
	{
		x = tmp;
		while (x < x_max)
			my_pixel_put(data, x++, y, color);
		y++;
	}
}

void	normalize_angle(t_cub3d *data)
{
	data->ray_angle = remainder(data->ray_angle, (2 * M_PI));
	if (data->ray_angle < 0)
		data->ray_angle = (2 * M_PI) + data->ray_angle;
}
