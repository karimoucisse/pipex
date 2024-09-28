/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:35:24 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "pipex_bonus.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	ft_free_lst(t_px_list *lst)
{
	if (lst == NULL)
		return (1);
	if (lst->cmd_paths)
		ft_free_tab(lst->cmd_paths);
	if (lst->cmd_args)
		free_3d_tab(lst->cmd_args);
	if (lst->fd_in > 0 && !lst->is_heredoc)
		close(lst->fd_in);
	if (lst->fd_in > 0 && lst->is_heredoc)
		unlink(".heredoc");
	if (lst->fd_out > 0)
		close(lst->fd_out);
	if (lst->limiter)
		free(lst->limiter);
	free(lst);
	return (1);
}

void	free_3d_tab(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_find_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*cmd_l;

	i = 0;
	cmd_l = ft_strjoin("/", cmd);
	if (!cmd_l)
		return (0);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], cmd_l);
		if (access(tmp, F_OK) == 0 || !tmp)
		{
			free(cmd_l);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free(cmd_l);
	return (ft_strdup(cmd));
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	int		i;
	char	*cmd_path;

	i = 0;
	while (*env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
			path = ft_strtrim(*env, "PATH=");
		env++;
	}
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	free(path);
	if (!paths)
		return (0);
	cmd_path = ft_find_path(paths, cmd);
	ft_free_tab(paths);
	return (cmd_path);
}
