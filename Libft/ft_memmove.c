/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:47:51 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/30 14:40:21 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// like memcpy but can handle value that overlap
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (dst);
	if (dst > src)
	{
		while (n > 0)
		{
			((char *)dst)[n -1] = ((char *)src)[n -1];
			n--;
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
