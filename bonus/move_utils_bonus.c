/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:46:10 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/30 14:08:10 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	down(t_cub3d *data)
{
	float	new_x;
	float	new_y;

	data->move_step = -1 * data->move_speed;
	new_x = data->p_x + cos(data->angle) * data->move_step;
	new_y = data->p_y + sin(data->angle) * data->move_step;
	if (!has_wall(data, new_x, new_y) && check_position_p(data, new_x, new_y)
		&& (data->map[(int)(data->p_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != '1'
		|| data->map[(int)(new_y / TILE_SIZE)]
		[(int)(data->p_x / TILE_SIZE)] != '1'))
	{
		data->p_x = new_x;
		data->p_y = new_y;
	}
}

void	left(t_cub3d *data)
{
	float	new_x;
	float	new_y;

	data->move_step = data->move_speed;
	new_x = data->p_x + cos(data->angle - (M_PI / 2)) * data->move_step;
	new_y = data->p_y + sin(data->angle - (M_PI / 2)) * data->move_step;
	if (!has_wall(data, new_x, new_y) && check_position_p(data, new_x, new_y)
		&& (data->map[(int)(data->p_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != '1'
		|| data->map[(int)(new_y / TILE_SIZE)]
		[(int)(data->p_x / TILE_SIZE)] != '1'))
	{
		data->p_x = new_x;
		data->p_y = new_y;
	}
}

void	right(t_cub3d *data)
{
	float	new_x;
	float	new_y;

	data->move_step = data->move_speed;
	new_x = data->p_x + cos(data->angle + (M_PI / 2)) * data->move_step;
	new_y = data->p_y + sin(data->angle + (M_PI / 2)) * data->move_step;
	if (!has_wall(data, new_x, new_y) && check_position_p(data, new_x, new_y)
		&& (data->map[(int)(data->p_y / TILE_SIZE)]
		[(int)(new_x / TILE_SIZE)] != '1'
		|| data->map[(int)(new_y / TILE_SIZE)]
		[(int)(data->p_x / TILE_SIZE)] != '1'))
	{
		data->p_x = new_x;
		data->p_y = new_y;
	}
}

void	rot_left(t_cub3d *data)
{
	data->angle += -1 * data->rot_speed;
}

void	rot_right(t_cub3d *data)
{
	data->angle += 1 * data->rot_speed;
}
