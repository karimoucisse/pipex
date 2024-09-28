/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:42:58 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../Libft/libft.h"

t_px_list	*lst_new(void)
{
	t_px_list	*lst;

	lst = malloc(sizeof(t_px_list));
	if (lst == NULL)
		return (0);
	lst->fd_in = 0;
	lst->fd_out = 0;
	lst->is_infile = 1;
	lst->cmd_paths = NULL;
	lst->cmd_args = NULL;
	return (lst);
}

int	ft_handle_cmd_paths(char **av, char **env, char **path_tab, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (av[i][j] && av[i][j] != ' ')
			j++;
		if (j == 0)
			tmp = ft_strdup(av[i]);
		else
			tmp = ft_substr(av[i], 0, j);
		if (tmp == NULL)
			return (ft_free_tab(path_tab));
		path_tab[i] = get_cmd_path(tmp, env);
		free(tmp);
		if (path_tab[i] == NULL)
			return (ft_free_tab(path_tab));
		i++;
	}
	return (1);
}

char	**ft_fill_cmd_paths(char **av, char **env)
{
	char	**path_tab;
	char	*tmp;

	tmp = NULL;
	path_tab = malloc(sizeof(char *) * (2 + 1));
	if (path_tab == NULL)
		return (0);
	if (!ft_handle_cmd_paths(av, env, path_tab, tmp))
	{
		ft_free_tab(path_tab);
		return (0);
	}
	path_tab[2] = NULL;
	return (path_tab);
}

char	***ft_fill_cmd_args(char **av)
{
	int		i;
	char	***args_tab;

	i = 0;
	args_tab = malloc(sizeof(char *) * (2 + 1));
	if (args_tab == NULL)
		return (0);
	while (i < 2)
	{
		args_tab[i] = ft_split(av[i], ' ');
		if (args_tab[i] == NULL)
		{
			free_3d_tab(args_tab);
			return (0);
		}
		i++;
	}
	args_tab[i] = NULL;
	return (args_tab);
}

t_px_list	*ft_fill_lst(char **av, int ac, char **env)
{
	t_px_list	*lst;

	lst = lst_new();
	if (lst == NULL)
		return (0);
	lst->cmd_paths = ft_fill_cmd_paths(&av[2], env);
	lst->cmd_args = ft_fill_cmd_args(&av[2]);
	if (lst->cmd_args == NULL || lst->cmd_paths == NULL)
		return (0);
	lst->fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if ((access(av[1], F_OK) == 0 && access(av[1], R_OK) == -1)
		|| access(av[1], F_OK) == -1)
		lst->is_infile = 0;
	else
		lst->fd_in = open(av[1], O_RDONLY);
	if (lst->fd_out == -1)
		close(lst->fd_out);
	return (lst);
}
