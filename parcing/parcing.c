/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:51:17 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/09 15:35:31 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	stock_var(t_cub3d *data, char *key, char *value)
{
	if (!key || !value)
		print_error("Error\n");
	if (!ft_strcmp(key, "NO") && !data->north)
	{
		open_tex_file(value, key);
		data->north = value;
	}
	else if (!ft_strcmp(key, "SO") && !data->soulth)
	{
		open_tex_file(value, key);
		data->soulth = value;
	}
	else if (!ft_strcmp(key, "WE") && !data->west)
	{
		open_tex_file(value, key);
		data->west = value;
	}
	else if (!ft_strcmp(key, "EA") && !data->east)
	{
		open_tex_file(value, key);
		data->east = value;
	}
	else
		floor_ceiling(data, value, key);
}

void	check_variable(t_cub3d *data, char *line)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = NULL;
	value = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			key = ft_substr(line, 0, i);
			while ((line[i] >= 9 && line[i] <= 13) || line[i] == 32)
				i++;
			value = ft_substr(line, i, ft_strlen(line));
			break ;
		}
		i++;
	}
	stock_var(data, key, value);
	free (key);
	free (value);
}

void	newline(char *line, int fd, char *tmp)
{
	if (!ft_strcmp(line, "\n"))
	{
		close (fd);
		free (line);
		free (tmp);
		print_error("Error in map\n");
	}
}

void	count_height_width(t_cub3d *data, char *line, int fd)
{
	line = get_next_line(fd);
	empty_line(line);
	while (!ft_strcmp(line, "\n"))
	{
		free (line);
		line = get_next_line(fd);
		empty_line(line);
	}
	while (line)
	{
		newline(line, fd, data->tmp);
		if (data->width < my_strlen(line))
			data->width = my_strlen(line);
		data->height++;
		data->tmp = ft_strjoin_g(data->tmp, line);
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		exit (1);
}

void	read_map(t_cub3d *data, char *file)
{
	char	*line;
	int		fd;
	int		i;
	char	*str;

	i = 0;
	fd = open_file(file);
	while (i < 6)
	{
		line = get_next_line(fd);
		empty_line(line);
		if (!ft_strcmp(line, "\n"))
		{
			free (line);
			continue ;
		}
		str = ft_strtrim_line(line);
		check_variable(data, str);
		free (str);
		free (line);
		i++;
	}
	count_height_width(data, line, fd);
}
