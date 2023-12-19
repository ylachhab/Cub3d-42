/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 18:16:54 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/18 09:59:19 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	normalize_angle(t_cub3d *data)
{
	data->ray_angle = remainder(data->ray_angle, (2 * M_PI));
	if (data->ray_angle < 0)
		data->ray_angle = (2 * M_PI) + data->ray_angle;
}

float	distance_value(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	has_wall(t_cub3d *data, float x, float y)
{
	double	nextx;
	double	nexty;

	if (x < 0 || x > (data->width * TILE_SIZE) || y < 0
		|| y > (data->height * TILE_SIZE))
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
