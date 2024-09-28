/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:57:28 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../Libft/libft.h"
#include "../gnl/get_next_line.h"

void	ft_write_pipe(int arg_nbr)
{
	int	len;

	len = arg_nbr - 1;
	while (len > 0)
	{
		write(1, "pipe ", 5);
		len--;
	}
}

void	handle_error_msg(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
	exit(EXIT_FAILURE);
}

int	ft_handle_cmd_paths(char **av, t_px_list *lst, char **path_tab, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	while (i < lst->nbr_cmds)
	{
		j = 0;
		while (av[i][j] && av[i][j] != ' ')
			j++;
		tmp = ft_substr(av[i], 0, j);
		if (tmp == NULL)
			return (0);
		path_tab[i] = get_cmd_path(tmp, lst->env);
		if (path_tab[i] == NULL)
		{
			free(tmp);
			return (0);
		}
		free(tmp);
		i++;
	}
	return (1);
}

void	ft_check_args(int ac, char **av, char **env)
{
	if (!*env)
		handle_error_msg("No, env!\n");
	if ((((ft_strncmp(av[1], "here_doc", 8))
				|| (ft_strlen(av[1])) != 8)) && ac < 5)
		handle_error_msg("Error! There is less then 5 arguments\n");
	if ((!ft_strncmp(av[1], "here_doc", 8) && ft_strlen(av[1]) == 8) && ac < 6)
		handle_error_msg("Error! There is less then 6 arguments\n");
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
		exit(ft_free_lst(lst));
	if (ft_exec(lst) == 0)
		exit(ft_free_lst(lst));
	if (!lst->is_heredoc)
	{
		if ((access(av[1], F_OK) == 0 && access(av[1], R_OK) == -1)
			|| access(av[1], F_OK) == -1)
		{
			perror(av[1]);
			exit(ft_free_lst(lst));
		}
	}
	ft_free_lst(lst);
	exit(EXIT_SUCCESS);
}
