/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:10:40 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 17:52:19 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	check_floor_ceiling_var(int *var, char *value)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(value) - 1;
	while ((value[len] >= 9 && value[len] <= 13) || value[len] == 32)
		len--;
	check_comma(value);
	split_map(var, value);
}

void	floor_ceiling(t_cub3d *data, char *value, char *key)
{
	if (!ft_strcmp(key, "F") && data->floor[0] == 0
		&& data->floor[1] == 0 && data->floor[2] == 0)
		check_floor_ceiling_var(data->floor, value);
	else if (!ft_strcmp(key, "C") && data->ceiling[0] == 0
		&& data->ceiling[1] == 0 && data->ceiling[2] == 0)
		check_floor_ceiling_var(data->ceiling, value);
	else
	{
		free (key);
		free (value);
		print_error("Error in the element\n");
	}
}

void	stock_map(t_cub3d *data)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(data->tmp, '\n');
	while (split[i])
	{
		data->map[i] = ft_strdup(split[i]);
		i++;
	}
	free_str(split);
	free (data->tmp);
	data->map[i] = NULL;
}

void	valid_content(t_cub3d *data)
{
	int	i;
	int	j;
	int	nbr;

	i = 0;
	nbr = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != ' ' && data->map[i][j] != '1'
				&& data->map[i][j] != '0' && data->map[i][j] != 'N'
				&& data->map[i][j] != 'W' && data->map[i][j] != 'S'
				&& data->map[i][j] != 'E' && data->map[i][j] != '\n')
				error(data, "Error in content of map\n");
			if (data->map[i][j] == 'N' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'E')
				nbr++;
			j++;
		}
		i++;
	}
	if (nbr != 1)
		error(data, "Error in the content of map\n");
}
