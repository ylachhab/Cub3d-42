/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:15:06 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 18:05:29 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_minimap(t_cub3d *data)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < MINIMAP_HEIGHT && floor(data->p_y - MINIMAP_HEIGHT / 2 + i)
		/ TILE_SIZE < data->height)
	{
		j = 0;
		while (j < MINIMAP_WIDTH && floor(data->p_x - MINIMAP_WIDTH / 2 + j)
			/ TILE_SIZE < data->width)
		{
			color = get_color(data, j, i);
			my_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_player(t_cub3d *data)
{
	int	y;
	int	x;
	int	i;

	y = -RADIUS;
	while (y <= RADIUS)
	{
		x = (int)sqrt(RADIUS * RADIUS - y * y);
		i = (MINIMAP_WIDTH / 2) - x;
		while (i <= (MINIMAP_WIDTH / 2) + x)
		{
			my_pixel_put(data, i, ((MINIMAP_HEIGHT / 2) + y), 0xD90432);
			i++;
		}
		y++;
	}
}

void	set_tex(t_cub3d *data, t_img *tex, char *str)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, str,
			&tex->tex_x, &tex->tex_y);
	tex->addr_tex = (int *)mlx_get_data_addr(tex->img,
			&tex->bits_per_pixel, &tex->line_length,
			&tex->endian);
	if (!tex->img || !tex->addr_tex)
	{
		free(data->north);
		free(data->soulth);
		free(data->west);
		free(data->east);
		free_str(data->map);
		exit(1);
	}
}

void	center_mouse(t_cub3d *data)
{
	data->center_mouse = true;
	mlx_mouse_move(data->mlx_win, (WIDTH) / 2,
		data->mouse_y);
	data->mouse_x = (WIDTH) / 2;
}

int	mouse_hook(int x, int y, t_cub3d *data)
{
	float	new_x;
	float	p;

	if (data->mouse_show)
		return (0);
	if (x < 0 || y < 0 || x > WIDTH
		|| y > HEIGHT)
		return (center_mouse(data), 0);
	if (data->center_mouse == false)
	{
		new_x = x - data->mouse_x;
		p = new_x * MOUSE_ROT_SPEED;
		data->angle += p;
		data->mouse_x = x;
		data->mouse_y = y;
	}
	data->center_mouse = false;
	return (0);
}
