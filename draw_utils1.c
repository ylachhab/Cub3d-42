/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:16:54 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 17:36:33 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	distance_value(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	has_wall(t_cub3d *data, float x, float y)
{
	double	nextx;
	double	nexty;

	if (x < 0 || x >= data->width * TILE_SIZE || y < 0
		|| y >= data->height * TILE_SIZE)
		return (true);
	nextx = floor(x / TILE_SIZE);
	nexty = floor(y / TILE_SIZE);
	if (data->map[(int)nexty][(int)nextx] == '1')
		return (true);
	return (false);
}

void	ray_direction(t_cub3d *data, t_ray *ray)
{
	ray->found_horz_wall = false;
	if (data->ray_angle > 0 && data->ray_angle <= M_PI)
		ray->ray_facing_down = true;
	else
		ray->ray_facing_down = false;
	if (data->ray_angle < (M_PI / 2) || data->ray_angle >= ((3 * M_PI) / 2))
		ray->ray_facing_right = true;
	else
		ray->ray_facing_right = false;
	ray->yintercept = floor(data->p_y / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_down)
		ray->yintercept += TILE_SIZE;
}

void	put_wall_color(t_cub3d *data, t_ray ray, int a, int x)
{
	t_img	tab;
	int		color;
	int		off;
	int		var;
	int		y;

	tab = get_img(data, ray);
	if (data->hit_vertical)
		off = fmod(data->wallhity, TILE_SIZE) * tab.tex_y / TILE_SIZE;
	else
		off = fmod(data->wallhitx, TILE_SIZE) * tab.tex_x / TILE_SIZE;
	y = -1;
	while (++y < (HEIGHT))
	{
		if (y >= data->begin && y < data->end)
		{
			var = ((y - data->begin) * tab.tex_y) / data->wall_height;
			color = tab.addr_tex[var * tab.tex_x + off];
			my_pixel_put(data, x, y, a | color);
		}
		else if (y < data->begin)
			my_pixel_put_floor(data, x, y, data->ceiling);
		else if (y > data->end)
			my_pixel_put_floor(data, x, y, data->floor);
	}
}

void	render_projected_walls(t_cub3d *data, int column, t_ray	ray)
{
	float	dis_proj_plane;
	int		x;
	int		a;

	data->distance *= cos(data->ray_angle - data->angle);
	dis_proj_plane = ((WIDTH) / 2) / tan(data->fov_angle / 2);
	data->wall_height = (TILE_SIZE / data->distance) * dis_proj_plane;
	x = column * data->wall_strip;
	data->begin = ((HEIGHT) / 2) - (data->wall_height / 2);
	data->end = ((HEIGHT) / 2) + (data->wall_height / 2);
	if (data->distance > 400)
		a = 150;
	else
		a = (150 * data->distance) / 400;
	a <<= 24;
	put_wall_color(data, ray, a, x);
}
