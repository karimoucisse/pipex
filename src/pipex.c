/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:25:04 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../Libft/libft.h"

void	ft_check_args(int ac, char **av, char **env)
{
	char	*error_txt;

	error_txt = "Error! There is more or less then 5 arguments";
	if (!*env)
	{
		write(1, "No, env!", 8);
		exit(EXIT_FAILURE);
	}
	if (ac != 5)
	{
		write(1, error_txt, ft_strlen(error_txt));
		exit(EXIT_FAILURE);
	}
	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) == -1)
	{
		perror(av[ac - 1]);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	t_px_list	*lst;

	ft_check_args(ac, av, env);
	lst = ft_fill_lst(av, ac, env);
	if (!lst)
	{
		ft_free_lst(lst);
		exit(EXIT_FAILURE);
	}
	if (ft_exec(lst, env) == 0)
	{
		ft_free_lst(lst);
		exit(EXIT_FAILURE);
	}
	ft_free_lst(lst);
	if ((access(av[1], F_OK) == 0 && access(av[1], R_OK) == -1)
		|| access(av[1], F_OK) == -1)
	{
		perror(av[1]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
