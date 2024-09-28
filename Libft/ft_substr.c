/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:55:24 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/29 18:00:27 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (0);
	if (start <= ft_strlen(s))
	{
		while (s[start] && i < (len))
		{
			new_str[i] = s[start];
			i++;
			start++;
		}
	}
	new_str[i] = '\0';
	return (new_str);
}
