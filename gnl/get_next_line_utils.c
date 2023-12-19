/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:50:59 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/29 11:33:52 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen_g(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_g(char *ptr, int c)
{
	int		j;
	char	a;

	j = 0;
	if (!ptr)
		return (NULL);
	a = (char)c;
	if (a == '\0')
		return (ptr + ft_strlen_g(ptr));
	while (ptr[j])
	{
		if (ptr[j] == a)
			return (ptr + j);
		j++;
	}
	return (NULL);
}

char	*ft_strdup_g(const char *s1)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	ptr = malloc (sizeof(char) * i + 1);
	if (!ptr)
		return (NULL);
	while (j < i)
	{
		ptr[j] = s1[j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_strjoin_g(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_strdup_g("");
	if (!s2 || !s1)
		return (NULL);
	str = (char *)malloc(sizeof(char) *(ft_strlen_g(s1) + ft_strlen_g(s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i++] = s2[j++];
	}
	str[ft_strlen_g(s1) + ft_strlen_g(s2)] = '\0';
	free(s1);
	return (str);
}
