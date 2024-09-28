/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:23:06 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/26 17:44:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*tabs;

	i = 0;
	tabs = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (tabs == NULL)
		return (0);
	while (s[i])
	{
		tabs[i] = (*f)(i, s[i]);
		i++;
	}
	tabs[i] = '\0';
	return (tabs);
}
