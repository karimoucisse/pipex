/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:41:26 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/29 17:41:15 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[k] && (k < (size_t)len))
	{
		i = k;
		j = 0;
		while (big[i] && (i < (size_t)len))
		{
			if (big[i] != little[j])
				j = 0;
			if (big[i] == little[j])
				j++;
			if (j == ft_strlen(little))
				return (&((char *)big)[i - (j - 1)]);
			i++;
		}
		k++;
	}
	return (0);
}
