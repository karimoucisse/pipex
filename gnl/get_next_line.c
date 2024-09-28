/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:12:36 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../Libft/libft.h"

char	*handle_temp_var(char *remain_char, char *buffer)
{
	char	*temp;

	if (!remain_char)
		remain_char = ft_strdup("");
	temp = remain_char;
	remain_char = ft_strjoin(temp, buffer);
	if (!remain_char)
		return (0);
	free(temp);
	temp = NULL;
	return (remain_char);
}

char	*fill_buffer(int fd, char *remain_char)
{
	int		count_bytes;
	char	*buffer;

	count_bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while (count_bytes > 0)
	{
		count_bytes = read(fd, buffer, BUFFER_SIZE);
		if (count_bytes > 0)
		{
			buffer[count_bytes] = '\0';
			remain_char = handle_temp_var(remain_char, buffer);
			if (ft_strchr_gnl(buffer, '\n'))
				count_bytes = 0;
		}
	}
	free(buffer);
	return (remain_char);
}

char	*fill_line(char *buffer)
{
	char	*str_cpy;
	int		i;

	if (!buffer || ft_strlen(buffer) == 0)
		return (0);
	str_cpy = NULL;
	i = ft_strchr_gnl(buffer, '\n');
	if (i == 0)
		i = ft_strlen(buffer);
	str_cpy = malloc(sizeof(char *) * i);
	if (!str_cpy)
		return (0);
	ft_strlcpy_gnl(str_cpy, buffer, i + 1);
	return (str_cpy);
}

char	*fill_remain_char(char *buffer)
{
	char	*remain_char;
	int		i;

	if (!buffer || ft_strlen(buffer) == 0)
		return (0);
	remain_char = NULL;
	i = ft_strchr_gnl(buffer, '\n');
	if ((int)ft_strlen(buffer) == i)
		return (0);
	remain_char = ft_strdup(&(buffer[i]));
	if (!remain_char)
		return (0);
	return (remain_char);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*str_line;
	static char	*remain_char;

	str_line = NULL;
	if ((BUFFER_SIZE <= 0 || fd < 0) || read(fd, 0, 0) < 0)
	{
		free(remain_char);
		remain_char = NULL;
		return (0);
	}
	buffer = fill_buffer(fd, remain_char);
	if (!buffer || ft_strlen(buffer) == 0 || !ft_strchr_gnl(buffer, '\n'))
	{
		remain_char = NULL;
		return (buffer);
	}
	str_line = fill_line(buffer);
	remain_char = fill_remain_char(buffer);
	free(buffer);
	return (str_line);
}
