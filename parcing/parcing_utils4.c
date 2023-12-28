/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:18:47 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/26 15:30:01 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	error(t_cub3d *data, char *str)
{
	free_str(data->map);
	print_error(str);
}

void	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit (1);
}

void	is_space(t_cub3d *data, char *str, int *i)
{
	int	j;

	j = 0;
	while (data->map[*i][j])
	{
		str[j] = data->map[*i][j];
		if (str[j] == '\n')
			str[j] = ' ';
		j++;
	}
	while (j < data->width)
		str[j++] = ' ';
	str[j] = '\0';
	data->map[*i] = str;
}

int	my_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

void	valid_map(t_cub3d *data)
{
	char	*str;
	int		i;
	int		len;

	i = 1;
	while (data->map[i] && i < (data->height - 1))
	{
		str = ft_strtrim_line(data->map[i]);
		len = ft_strlen(str) - 1;
		if (str[0] == '\0')
		{
			i++;
			free(str);
			continue ;
		}
		if (str[0] != '1' || str[len] != '1')
		{
			free(str);
			error(data, "Error in map\n");
		}
		free(str);
		i++;
	}
}
