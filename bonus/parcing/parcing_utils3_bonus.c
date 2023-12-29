/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:12:17 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 17:52:23 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	check_map_lenght(t_cub3d *data)
{
	char	*tmp;
	char	*str;
	int		i;

	i = 0;
	while (data->map[i])
	{
		if (data->width > my_strlen(data->map[i]))
		{
			tmp = data->map[i];
			str = malloc(sizeof(char *) * data->width);
			if (!str)
				exit(1);
			is_space(data, str, &i);
			free(tmp);
		}
		i++;
	}
}

void	check_player(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'S')
			{
				if ((i > 0 && data->map[i - 1][j] == ' ')
					|| (i < (data->height - 1) && data->map[i + 1][j] == ' ')
					|| (j > 0 && data->map[i][j - 1] == ' ')
					|| (j < data->width && data->map[i][j + 1] == ' ')
					|| (data->map[i][j + 1] == '\0'))
					error(data, "Error map is not closed\n");
				data->p_x = (j * TILE_SIZE) + (TILE_SIZE / 2);
				data->p_y = (i * TILE_SIZE) + (TILE_SIZE / 2);
			}
			j++;
		}
		i++;
	}
}

void	check_space(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '0')
			{
				if ((i > 0 && data->map[i - 1][j] == ' ')
					|| (i < (data->height - 1) && data->map[i + 1][j] == ' ')
					|| (j > 0 && data->map[i][j - 1] == ' ')
					|| (j < data->width && data->map[i][j + 1] == ' ')
					|| (data->map[i][j + 1] == '\0'))
					error(data, "Error map is not closed\n");
			}
			j++;
		}
		i++;
	}
}

void	is_wall(char *str, t_cub3d *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
		{
			free(str);
			free_str(data->map);
			print_error("Map is not closed\n");
		}
		i++;
	}
	free(str);
}

void	map_close(t_cub3d *data)
{
	char	*str;

	str = ft_strtrim_line(data->map[0]);
	is_wall(str, data);
	str = ft_strtrim_line(data->map[data->height - 1]);
	is_wall(str, data);
}
