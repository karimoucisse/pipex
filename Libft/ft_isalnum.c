/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 00:25:56 by kcisse            #+#    #+#             */
/*   Updated: 2024/05/30 14:34:58 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// checks for an alphanumeric character;
int	ft_isalnum(int i)
{
	if (ft_isdigit(i))
		return (1);
	if (ft_isalpha(i))
		return (1);
	return (0);
}
