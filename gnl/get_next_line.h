/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 09:59:23 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 13:45:05 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// GET_NEXT_LINE FUNCTIONS
char	*get_next_line(int fd);
char	*fill_buffer(int fd, char *buffer);
char	*fill_line(char *buffer);
char	*fill_remain_char(char *buffer);
char	*handle_temp_var(char *remain_char, char *buffer);

// UTILS
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcpy_gnl(char *dst, const char *src, size_t size);
int		ft_strchr_gnl(const char *s, int c);

#endif
