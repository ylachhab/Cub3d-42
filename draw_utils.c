/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 13:35:39 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/27 12:08:55 by ylachhab         ###   ########.fr       */
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
		data->hit_vertical = false;
	}
	else
	{
		data->wallhitx = ray->wall_hit_vertx;
		data->wallhity = ray->wall_hit_verty;
		data->distance = ray->vert_distance;
		data->hit_vertical = true;
	}
}

t_img	get_img(t_cub3d *data, t_ray ray)
{
	t_img	tab[4];
	int		index;

	index = 0;
	tab[0] = data->img_n;
	tab[1] = data->img_s;
	tab[2] = data->img_w;
	tab[3] = data->img_e;
	if (!ray.ray_facing_down && !data->hit_vertical)
		index = 0;
	else if (ray.ray_facing_down && !data->hit_vertical)
		index = 1;
	else if (ray.ray_facing_right && data->hit_vertical)
		index = 3;
	else if (!ray.ray_facing_right && data->hit_vertical)
		index = 2;
	return (tab[index]);
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
	render_projected_walls(data, column, ray);
}
