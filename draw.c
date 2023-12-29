/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:09:12 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 13:49:32 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_position_p(t_cub3d *data, double x, double y)
{
	double	i;
	double	j;

	i = y - 2;
	while (i <= y + 2)
	{
		j = x - 2;
		while (j <= x + 2)
		{
			if (data->map[(int)i / TILE_SIZE][(int)j / TILE_SIZE] == '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	my_pixel_put(t_cub3d *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->img.addr + (y * data->img.line_length + x
			* (data->img.bits_per_pixel / 8));
	*(int *)dst = color;
}

void	cast_rays(t_cub3d *data)
{
	int	column;

	column = 0;
	data->ray_angle = data->angle - (data->fov_angle / 2);
	while (column < data->nbr_rays)
	{
		normalize_angle(data);
		cast(data, column);
		data->ray_angle += data->fov_angle / data->nbr_rays;
		column++;
	}
}

void	draw(t_cub3d *data)
{
	t_line	line;

	cast_rays(data);
	draw_minimap(data);
	draw_player(data);
	draw_line(data, &line);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int	cross_click(t_cub3d	*data)
{
	int	i;

	i = 0;
	while (i < data->height)
	{
		free(data->map[i]);
		data->map[i] = NULL;
		i++;
	}
	free(data->map);
	exit(0);
	return (1);
}

void	load_game(t_cub3d *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH,
			HEIGHT, "CUB3D");
	data->img.img = mlx_new_image(data->mlx, WIDTH,
			HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	if (!data->mlx || !data->mlx_win || !data->img.img || !data->img.addr)
	{
		free_str(data->map);
		exit(1);
	}
	data->center_mouse = false;
	mlx_mouse_move(data->mlx_win, (WIDTH) / 2,
		(HEIGHT) / 2);
	mlx_mouse_get_pos(data->mlx_win, &data->mouse_x, &data->mouse_y);
	set_tex(data, &data->img_n, "wall3.xpm");
	set_tex(data, &data->img_s, "wall1.xpm");
	set_tex(data, &data->img_w, "wall.xpm");
	set_tex(data, &data->img_e, "wall2.xpm");
	mlx_hook(data->mlx_win, 2, 0, &keypressed, data);
	mlx_hook(data->mlx_win, 3, 0, &keyrelease, data);
	mlx_hook(data->mlx_win, 17, 0, &cross_click, data);
	mlx_hook(data->mlx_win, 6, 0, mouse_hook, data);
	mlx_loop_hook(data->mlx, &move, data);
	mlx_loop(data->mlx);
}
