/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:14:51 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/30 14:46:18 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// count the number of string that are going to be split
int	count_chars(char const *s, char c)
{
	int	b;
	int	len;

	b = 0;
	len = 0;
	while (*s)
	{
		b = 0;
		while ((*s == c) && *s)
			s++;
		while ((*s != c) && *s)
		{
			if (b == 0)
			{
				b = 1;
				len++;
			}
			s++;
		}
	}
	return (len);
}

int	malloc_char_tab(char **chars_tab, int i, int len)
{
	int	j;

	j = 0;
	chars_tab[i] = malloc(sizeof(char) * (len + 1));
	if (chars_tab[i] == NULL)
	{
		while (j <= i)
		{
			free(chars_tab[j]);
			j++;
		}
		free(chars_tab);
		return (0);
	}
	return (1);
}

// fill the table chars_tab with the string
// that are goin to be split
int	tab_filler(const char *s, char c, char **chars_tab)
{
	int	len;
	int	i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while ((*s != c) && *s)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (!malloc_char_tab(chars_tab, i, len))
				return (0);
			ft_strlcpy(chars_tab[i], s - len, len +1);
			i++;
		}
	}
	chars_tab[i] = 0;
	return (1);
}

// split a string "s" by the value "c";
char	**ft_split(char const *s, char c)
{
	int		len;
	char	**chars_tab;

	len = count_chars(s, c);
	chars_tab = malloc(sizeof(char *) * (len + 1));
	if (chars_tab == NULL)
		return (0);
	if (!tab_filler(s, c, chars_tab))
		return (0);
	return (chars_tab);
}
