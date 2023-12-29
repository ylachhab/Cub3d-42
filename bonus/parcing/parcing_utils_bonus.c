/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nel-baz <nel-baz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:44:58 by ylachhab          #+#    #+#             */
/*   Updated: 2023/12/29 17:52:10 by nel-baz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	check_file_name(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (file[len] != 'b' || file[len - 1] != 'u' || file[len - 2] != 'c'
		|| file[len - 3] != '.')
		print_error("Error in file name\n");
}

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		print_error("Error in file\n");
	return (fd);
}

void	empty_line(char *line)
{
	if (!line)
		print_error("Error in file content\n");
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strtrim_line(char const *s1)
{
	char	*str;
	size_t	debut;
	size_t	fin;
	size_t	i;

	i = 0;
	debut = 0;
	if (!s1)
		return (NULL);
	fin = strlen(s1);
	while (s1[debut] && ((s1[debut] >= 9 && s1[debut] <= 13)
			|| s1[debut] == 32))
		debut++;
	while (fin > debut && ((s1[fin - 1] >= 9 && s1[fin - 1] <= 13)
			|| s1[fin - 1] == 32))
		fin--;
	str = (char *)malloc(sizeof(char) * (fin - debut + 1));
	if (!str)
		return (0);
	while (debut < fin)
		str[i++] = s1[debut++];
	return (str[i] = '\0', str);
}
