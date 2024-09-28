/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:48:03 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/30 14:40:17 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *p1, const void *p2, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (((unsigned char *)p1)[i] != ((unsigned char *)p2)[i])
			return (((unsigned char *)p1)[i] - ((unsigned char *)p2)[i]);
		i++;
	}
	return (0);
}
