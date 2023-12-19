/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylachhab <ylachhab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 20:48:22 by ylachhab          #+#    #+#             */
/*   Updated: 2023/07/29 11:33:05 by ylachhab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif

char	*ft_line(char *str);
char	*ft_read(int fd, char *str);
char	*ft_new_str(char *str);
char	*get_next_line(int fd);
char	*ft_strchr_g(char *str, int c);
char	*ft_strjoin_g(char *s1, char *s2);
char	*ft_strdup_g(const char *s1);
int		ft_strlen_g(char *s);

#endif
