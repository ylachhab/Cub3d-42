/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:35:39 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/18 21:10:54 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	horz_intersection(t_cub3d *data, t_ray *ray)
{
	ray->xintercept = data->p_x + ((ray->yintercept - data->p_y)
			/ tan(data->ray_angle));
	ray->ystep = TILE_SIZE;
	if (!ray->ray_facing_down)
		ray->ystep *= -1;
	ray->xstep = TILE_SIZE / tan(data->ray_angle);
	if ((!ray->ray_facing_right && ray->xstep > 0)
		|| (ray->ray_facing_right && ray->xstep < 0))
		ray->xstep *= -1;
	while (ray->xintercept >= 0 && ray->xintercept < (data->width * TILE_SIZE)
		&& ray->yintercept >= 0 && ray->yintercept < (data->height * TILE_SIZE))
	{
		ray->y = ray->yintercept;
		if (!ray->ray_facing_down)
			ray->y--;
		if (has_wall(data, ray->xintercept, ray->y))
		{
			ray->found_horz_wall = true;
			ray->wall_hit_horzx = ray->xintercept;
			ray->wall_hit_horzy = ray->yintercept;
			break ;
		}
		ray->xintercept += ray->xstep;
		ray->yintercept += ray->ystep;
	}
}

void	vert_intersection(t_cub3d *data, t_ray *ray)
{
	ray->yintercept = data->p_y + ((ray->xintercept - data->p_x)
			* tan(data->ray_angle));
	ray->xstep = TILE_SIZE;
	if (!ray->ray_facing_right)
		ray->xstep *= -1;
	ray->ystep = TILE_SIZE * tan(data->ray_angle);
	if ((!ray->ray_facing_down && ray->ystep > 0)
		|| (ray->ray_facing_down && ray->ystep < 0))
		ray->ystep *= -1;
	while (ray->xintercept >= 0 && ray->xintercept < (data->width * TILE_SIZE)
		&& ray->yintercept >= 0 && ray->yintercept < (data->height * TILE_SIZE))
	{
		ray->x = ray->xintercept;
		if (!ray->ray_facing_right)
			ray->x--;
		if (has_wall(data, ray->x, ray->yintercept))
		{
			ray->found_vert_wall = true;
			ray->wall_hit_vertx = ray->xintercept;
			ray->wall_hit_verty = ray->yintercept;
			break ;
		}
		ray->xintercept += ray->xstep;
		ray->yintercept += ray->ystep;
	}
}

void	check_distance(t_cub3d *data, t_ray *ray)
{
	if (ray->found_horz_wall)
		ray->horz_distance = distance_value(data->p_x, data->p_y,
				ray->wall_hit_horzx, ray->wall_hit_horzy);
	else
		ray->horz_distance = INT_MAX;
	if (ray->found_vert_wall)
		ray->vert_distance = distance_value(data->p_x, data->p_y,
				ray->wall_hit_vertx, ray->wall_hit_verty);
	else
		ray->vert_distance = INT_MAX;
	if (ray->horz_distance < ray->vert_distance)
	{
		data->wallhitx = ray->wall_hit_horzx;
		data->wallhity = ray->wall_hit_horzy;
		data->distance = ray->horz_distance;
	}
	else
	{
		data->wallhitx = ray->wall_hit_vertx;
		data->wallhity = ray->wall_hit_verty;
		data->distance = ray->vert_distance;
		data->hit_vertical = true;
	}
}

void	my_put_color(t_cub3d *data, int x, int y, int color)
{
	// int	x_max;
	int	y_max;
	int	tmp;
	int	p;

	tmp = x;
	p = y;
	// x_max = x + data->wall_strip;
	y_max = y + data->wall_height;
	while (y < y_max)
	{
		// x = tmp;
		// while (x < x_max)
		// {
			if (p == y || x == tmp)
				my_pixel_put(data, x, y, 0x568DBA);
			else
				my_pixel_put(data, x, y, color);
			// x++;
		// }
		y++;
	}
}

void	render_projected_walls(t_cub3d *data, int column)
{
	float	dis_proj_plane;
	float	end;
	float	begin;
	int		x;
	int		y;

	dis_proj_plane = ((data->width * TILE_SIZE) / 2) / tan(data->fov_angle / 2);
	data->wall_height = (TILE_SIZE / data->distance) * dis_proj_plane;
	x = column * data->wall_strip;
	begin = ((data->height * TILE_SIZE) / 2) - (data->wall_height / 2);
	end = ((data->height * TILE_SIZE) / 2) + (data->wall_height / 2);
	y = 0;
	while (y >= 0 && y < (data->height * TILE_SIZE))
	{
		if (y >= begin && y <= end)
			my_pixel_put(data, x, y, 0x568DBA);
		else if (y < begin)
			my_pixel_put(data, x, y, 0xff);
		else if (y > end)
			my_pixel_put(data, x, y, 0xff00);
		y++;
	}
}

void	cast(t_cub3d *data, int column)
{
	t_ray	ray;

	data->hit_vertical = false;
	ray_direction(data, &ray);
	ray.wall_hit_horzx = 0;
	ray.wall_hit_horzy = 0;
	horz_intersection(data, &ray);
	ray.wall_hit_vertx = 0;
	ray.wall_hit_verty = 0;
	ray.found_vert_wall = false;
	ray.xintercept = floor(data->p_x / TILE_SIZE) * TILE_SIZE;
	if (ray.ray_facing_right)
		ray.xintercept += TILE_SIZE;
	vert_intersection(data, &ray);
	check_distance(data, &ray);
	render_projected_walls(data, column);
}
