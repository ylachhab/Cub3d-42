/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 20:09:12 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/27 16:51:10 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_cub3d *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
	*(int *)dst = color;
}

void	my_pixel_put_floor(t_cub3d *data, int x, int y, int *color)
{
	char	*dst;

	dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
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
	x_max = x + TILE_SIZE;
	y_max = y + TILE_SIZE;
	while (y < y_max)
	{
		x = tmp;
		while (x < x_max)
		{
			// if (p == y || x == tmp)
			// 	my_pixel_put(data, x, y, 0x568DBA);
			// else
				my_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				put_color(data, (j * TILE_SIZE) * MINIMAP_SCALE,
					(i * TILE_SIZE) * MINIMAP_SCALE, 0x000000);
			else if (data->map[i][j] == '0')
				put_color(data, (j * TILE_SIZE) * MINIMAP_SCALE,
					(i * TILE_SIZE) * MINIMAP_SCALE, 0xFFFFFF);
			else if (data->map[i][j] == ' ')
				put_color(data, (j * TILE_SIZE) * MINIMAP_SCALE,
					(i * TILE_SIZE) * MINIMAP_SCALE, 0x9C9C9C);
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
		i = data->p_x - x;
		while (i <= data->p_x + x)
		{
			my_pixel_put(data, i * MINIMAP_SCALE, (data->p_y + y)
				* MINIMAP_SCALE, 0xD61529);
			i++;
		}
		y++;
	}
}

void	draw_line(t_cub3d *data)
{
	float x,y,x1,y1,x2,y2,dx,dy,step;

	x2 = data->p_x * MINIMAP_SCALE;
	y2 = data->p_y * MINIMAP_SCALE;
	x1 = data->wallhitx * MINIMAP_SCALE;
	y1 = data->wallhity * MINIMAP_SCALE;
	dx = x1 - x2;
	dy = y1 - y2;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x2;
	y = y2;
	int i = 1;
	while (i <= step)
	{
		my_pixel_put(data, x, y, 0xF5F500);
		x = x + dx;
		y = y + dy;
		i++;
	}
}

void	draw_line1(t_cub3d *data)
{
	float x,y,x1,y1,x2,y2,dx,dy,step;

	x2 = data->p_x * MINIMAP_SCALE;
	y2 = data->p_y * MINIMAP_SCALE;
	x1 = (data->p_x + cos(data->angle) * 80) * MINIMAP_SCALE;
	y1 = (data->p_y + sin(data->angle) * 80) * MINIMAP_SCALE;
	dx = x1 - x2;
	dy = y1 - y2;
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx = dx / step;
	dy = dy / step;
	x = x2;
	y = y2;
	int i = 1;
	while (i <= step)
	{
		my_pixel_put(data, x, y, 0x0);
		x = x + dx;
		y = y + dy;
		i++;
	}
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
	cast_rays(data);
	draw_map(data);
	draw_player(data);
	draw_line1(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

void	set_tex(t_cub3d *data, t_img *tex, char *str)
{
	tex->img = mlx_xpm_file_to_image(data->mlx, str,
			&tex->tex_x, &tex->tex_y);
	tex->addr_tex = (int *)mlx_get_data_addr(tex->img,
			&tex->bits_per_pixel, &tex->line_length,
			&tex->endian);
}

void center_mouse(t_cub3d *data)
{
	data->center_mouse = true;
	mlx_mouse_move(data->mlx_win, (data->width * TILE_SIZE) / 2,
		data->mouse_y);
	data->mouse_x = (data->width * TILE_SIZE) / 2;
}

int mouse_hook(int x, int y, t_cub3d *data)
{
	float	new_x;
	float	p;

	if (data->mouse_show)
		return (0);
	if (x < 0 || y < 0 || x > data->width * TILE_SIZE
		|| y > data->height * TILE_SIZE)
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

void	load_game(t_cub3d *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, data->width * TILE_SIZE,
			data->height * TILE_SIZE, "CUB3D");
	data->img.img = mlx_new_image(data->mlx, data->width * TILE_SIZE,
			data->height * TILE_SIZE);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	data->center_mouse = false;
	mlx_mouse_move(data->mlx_win, (data->width * TILE_SIZE) / 2,
		(data->height * TILE_SIZE) / 2);
	mlx_mouse_get_pos(data->mlx_win, &data->mouse_x, &data->mouse_y);
	set_tex(data, &data->img_n, "wall3.xpm");
	set_tex(data, &data->img_s, "wall1.xpm");
	set_tex(data, &data->img_w, "wall.xpm");
	set_tex(data, &data->img_e, "wall2.xpm");
	mlx_hook(data->mlx_win, 2, 0, &keypressed, data);
	mlx_hook(data->mlx_win, 3, 0, &keyrelease, data);
	mlx_hook(data->mlx_win, 6, 0, mouse_hook, data);
	mlx_loop_hook(data->mlx, &move, data);
	mlx_loop(data->mlx);
}
