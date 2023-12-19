/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 20:20:06 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/27 13:36:48 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *str)
{
	char	*buff;
	int		n;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	n = 1;
	while (!ft_strchr_g(str, '\n') && n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
		{
			free(buff);
			free(str);
			str = NULL;
			return (NULL);
		}
		buff[n] = '\0';
		str = ft_strjoin_g(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_line(char *str)
{
	char	*line;
	int		j;

	j = 0;
	if (!str[j])
		return (NULL);
	while (str[j] && str[j] != '\n')
		j++;
	if (str[j] == '\n')
		j++;
	line = (char *)malloc(sizeof(char) * (j + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (str[j] && str[j] != '\n')
	{
		line[j] = str[j];
		j++;
	}
	if (str[j] == '\n')
	{
		line[j] = str[j];
		j++;
	}
	return (line[j] = '\0', line);
}

char	*ft_new_str(char *str)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	newline = (char *)malloc(sizeof(char) * ((ft_strlen_g(str) - i) + 1));
	if (!newline)
		return (NULL);
	j = 0;
	while (str[i])
		newline[j++] = str[i++];
	newline[j] = '\0';
	free(str);
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	line = ft_line(str);
	str = ft_new_str(str);
	return (line);
}
