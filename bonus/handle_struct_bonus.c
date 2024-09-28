/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_struct_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:20:22 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../Libft/libft.h"
#include "../gnl/get_next_line.h"

t_px_list	*lst_new(void)
{
	t_px_list	*lst;

	lst = malloc(sizeof(t_px_list));
	if (lst == NULL)
		return (0);
	lst->fd_in = -1;
	lst->fd_out = -1;
	lst->limiter = NULL;
	lst->is_heredoc = 0;
	lst->cmd_paths = NULL;
	lst->cmd_args = NULL;
	lst->nbr_cmds = 0;
	lst->env = NULL;
	return (lst);
}

char	**ft_fill_cmd_paths(char **av, t_px_list *lst)
{
	char	**path_tab;
	char	*tmp;

	tmp = 0;
	path_tab = malloc(sizeof(char *) * (lst->nbr_cmds + 1));
	if (path_tab == NULL)
		return (0);
	if (!ft_handle_cmd_paths(av, lst, path_tab, tmp))
	{
		ft_free_tab(path_tab);
		return (0);
	}
	path_tab[lst->nbr_cmds] = NULL;
	return (path_tab);
}

char	***ft_fill_cmd_args(char **av, int nbr_cmd)
{
	int		i;
	char	***args_tab;

	i = 0;
	args_tab = malloc(sizeof(char *) * (nbr_cmd + 1));
	if (args_tab == NULL)
		return (0);
	while (i < nbr_cmd)
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

int	ft_here_doc(t_px_list *lst)
{
	int		fd_h;
	char	*str;

	fd_h = open(".heredoc", O_CREAT | O_TRUNC | O_WRONLY | O_RDONLY, 0777);
	if (fd_h == -1)
	{
		perror("fd heredoc");
		return (0);
	}
	while (1)
	{
		ft_write_pipe(lst->nbr_cmds);
		write(1, "heredoc>", 8);
		str = get_next_line(0);
		if (!ft_strncmp(str, lst->limiter, ft_strlen(lst->limiter)))
			break ;
		if (str)
			write(fd_h, str, ft_strlen(str));
		free(str);
	}
	free(str);
	close(fd_h);
	lst->fd_in = open(".heredoc", O_RDONLY, 0644);
	return (1);
}

t_px_list	*ft_fill_lst(char **av, int ac, char **env)
{
	t_px_list	*lst;

	lst = lst_new();
	if (lst == NULL)
		return (0);
	if (!ft_strncmp(av[1], "here_doc", 8) && ft_strlen(av[1]) == 8)
		lst->is_heredoc = 1;
	lst->env = env;
	lst->nbr_cmds = ac - (3 + lst->is_heredoc);
	lst->cmd_paths = ft_fill_cmd_paths(&av[2 + lst->is_heredoc], lst);
	lst->cmd_args = ft_fill_cmd_args(&av[2 + lst->is_heredoc], lst->nbr_cmds);
	if (lst->cmd_args == NULL || lst->cmd_paths == NULL)
		return (0);
	lst->fd_out = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (lst->is_heredoc)
	{
		lst->limiter = ft_strjoin(av[2], "\n");
		if (!lst->limiter)
			return (0);
		if (!ft_here_doc(lst))
			return (0);
	}
	else
		lst->fd_in = open(av[1], O_RDONLY, 0644);
	return (lst);
}
