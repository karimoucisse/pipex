/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:45:32 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/06 14:17:44 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*joined_str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joined_str = malloc(sizeof(char) * ((s1_len + s2_len) + 1));
	if (joined_str == NULL)
		return (0);
	ft_memcpy(joined_str, s1, s1_len);
	ft_strlcpy(joined_str + s1_len, s2, s2_len + 1);
	return (joined_str);
}
