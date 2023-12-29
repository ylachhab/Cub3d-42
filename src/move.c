/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:28:27 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 17:11:43 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mouse(t_cub3d *data)
{
	if (!data->mouse_show)
	{
		mlx_mouse_show();
		data->mouse_show = true;
	}
	else
	{
		mlx_mouse_hide();
		data->mouse_show = false;
	}
}

int	keypressed(int keycode, t_cub3d *data)
{
	if (keycode == 53)
	{
		free(data->north);
		free(data->soulth);
		free(data->west);
		free(data->east);
		free_str(data->map);
		exit (1);
	}
	if (keycode == 13 || keycode == 126)
		data->up = true;
	if (keycode == 0)
		data->left = true;
	if (keycode == 1 || keycode == 125)
		data->down = true;
	if (keycode == 2)
		data->right = true;
	if (keycode == 123)
		data->rot_left = true;
	if (keycode == 124)
		data->rot_right = true;
	if (keycode == 12)
		ft_mouse(data);
	return (1);
}

int	keyrelease(int keycode, t_cub3d *data)
{
	if (keycode == 13 || keycode == 126)
		data->up = false;
	if (keycode == 0)
		data->left = false;
	if (keycode == 1 || keycode == 125)
		data->down = false;
	if (keycode == 2)
		data->right = false;
	if (keycode == 123)
		data->rot_left = false;
	if (keycode == 124)
		data->rot_right = false;
	return (1);
}

void	up(t_cub3d *data)
{
	float	new_x;
	float	new_y;

	data->move_step = 1 * data->move_speed;
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

int	move(t_cub3d *data)
{
	if (data->up == true)
		up(data);
	if (data->down == true)
		down(data);
	if (data->left == true)
		left(data);
	if (data->right == true)
		right(data);
	if (data->rot_left == true)
		rot_left(data);
	if (data->rot_right == true)
		rot_right(data);
	mlx_clear_window(data->mlx, data->mlx_win);
	draw(data);
	return (1);
}
