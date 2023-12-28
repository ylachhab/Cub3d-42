/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:19:14 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/28 16:40:07 by ylachhab         ###   ########.fr       */
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

int	get_color(t_cub3d *data, int j, int i)
{
	int	x;
	int	y;

	x = floor(data->p_x - MINIMAP_WIDTH / 2 + j);
	y = floor(data->p_y - MINIMAP_HEIGHT / 2 + i);
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (0x9C9C9C);
	else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == '1')
		return (0x000000);
	else if (data->map[y / TILE_SIZE][x / TILE_SIZE] == ' ')
		return (0x9C9C9C);
	return (0xFFFFFF);
}

void	draw_line(t_cub3d *data, t_line *line)
{
	int	i;

	i = 1;
	line->x2 = MINIMAP_WIDTH / 2;
	line->y2 = MINIMAP_HEIGHT / 2;
	line->x1 = (line->x2 + cos(data->angle) * 30);
	line->y1 = (line->y2 + sin(data->angle) * 30);
	line->dx = line->x1 - line->x2;
	line->dy = line->y1 - line->y2;
	if (fabs(line->dx) >= fabs(line->dy))
		line->step = fabs(line->dx);
	else
		line->step = fabs(line->dy);
	line->dx = line->dx / line->step;
	line->dy = line->dy / line->step;
	line->x = line->x2;
	line->y = line->y2;
	while (i <= line->step)
	{
		my_pixel_put(data, line->x, line->y, 0x0);
		line->x = line->x + line->dx;
		line->y = line->y + line->dy;
		i++;
	}
}
