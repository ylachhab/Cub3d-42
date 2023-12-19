/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:53:38 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/09 15:35:52 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	open_tex_file(char *value, char *key)
{
	int	fd;

	fd = open(value, O_RDONLY);
	if (fd == -1)
	{
		free (key);
		free (value);
		print_error("Error in file\n");
	}
	close(fd);
}

void	check_comma(char *value)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (value[i])
	{
		if (value[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		print_error("-----Error-----\n");
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		str[i] = NULL;
		i++;
	}
	free (str);
	str = NULL;
}

int	atoi_util(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		print_error("Error in color\n");
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + str[i] - '0';
		if (result > 255)
			print_error("Error in color\n");
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		print_error("Error in color\n");
	return (result);
}

void	split_map(int *var, char *value)
{
	char	**split;
	char	*str;
	int		i;

	i = 0;
	split = ft_split(value, ',');
	if (!split)
		print_error("Error in malloc\n");
	while (split[i])
		i++;
	if (i != 3)
	{
		free_str(split);
		print_error("Error in Floor or Ceiling\n");
	}
	i = 0;
	while (split[i])
	{
		str = ft_strtrim_line(split[i]);
		var[i] = atoi_util(str);
		free(str);
		i++;
	}
	free_str(split);
}
