/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:59:04 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 17:37:06 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_var(t_cub3d *data)
{
	data->height = 0;
	data->width = 0;
	data->north = NULL;
	data->soulth = NULL;
	data->east = NULL;
	data->west = NULL;
	data->tmp = NULL;
	data->ceiling[0] = 0;
	data->ceiling[1] = 0;
	data->ceiling[2] = 0;
	data->floor[0] = 0;
	data->floor[1] = 0;
	data->floor[2] = 0;
	data->p_x = 0;
	data->p_y = 0;
	data->move_speed = 7.0;
	data->rot_speed = 2 * (M_PI / 180);
	data->fov_angle = 60 * (M_PI / 180);
	data->wall_strip = 1;
	data->down = false;
	data->right = false;
	data->rot_left = false;
	data->rot_right = false;
	data->mouse_show = true;
	data->wall_height = 0;
}

int	cross_click(t_cub3d	*data)
{
	int	i;

	i = 0;
	free(data->north);
	free(data->soulth);
	free(data->west);
	free(data->east);
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

void	replace_player(t_cub3d *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				if (data->map[i][j] == 'N')
					data->angle = (3 * M_PI) / 2;
				else if (data->map[i][j] == 'S')
					data->angle = M_PI / 2;
				else if (data->map[i][j] == 'W')
					data->angle = M_PI;
				else if (data->map[i][j] == 'E')
					data->angle = 0;
				data->map[i][j] = '0';
			}
			j++;
		}
	}
}

void	parcing(t_cub3d *data, char *file)
{
	check_file_name(file);
	init_var(data);
	read_map(data, file);
	stock_map(data);
	valid_content(data);
	check_map_lenght(data);
	check_player(data);
	check_space(data);
	map_close(data);
	valid_map(data);
	replace_player(data);
}

int	main(int ac, char **av)
{
	t_cub3d	data;

	if (ac != 2)
		print_error("Error in the arguments\n");
	parcing(&data, av[1]);
	data.nbr_rays = WIDTH / data.wall_strip;
	load_game(&data);
	free(data.north);
	free(data.soulth);
	free(data.west);
	free(data.east);
	free_str(data.map);
}
