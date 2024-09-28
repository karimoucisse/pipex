/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:06:17 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/28 16:27:11 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_len(const char *s1, const char *set)
{
	int	i;
	int	len;
	int	b;

	i = 0;
	len = 0;
	b = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
	{
		len++;
		i++;
	}
	while (s1[i] && ft_strchr(set, s1[b]) && b > i)
	{
		len++;
		b--;
	}
	return (len);
}

void	fill_trimed_str(const char *s1, const char *set, char *copy)
{
	int	i;
	int	b;
	int	j;

	i = 0;
	b = ft_strlen(s1) - 1;
	j = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (s1[i] && ft_strchr(set, s1[b]) && b > i)
		b--;
	while (s1[i] && i <= b)
	{
		copy[j] = s1[i];
		i++;
		j++;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*trimed_str;

	len = ft_strlen(s1) - calc_len(s1, set);
	trimed_str = malloc(sizeof(char) * len + 1);
	if (trimed_str == NULL)
		return (0);
	fill_trimed_str(s1, set, trimed_str);
	trimed_str[len] = '\0';
	return (trimed_str);
}
