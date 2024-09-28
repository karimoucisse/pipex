/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:35:25 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft/libft.h"
#include "pipex.h"

int	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

int	ft_free_lst(t_px_list *lst)
{
	if (lst == NULL)
		return (1);
	if (lst->cmd_paths)
		ft_free_tab(lst->cmd_paths);
	if (lst->cmd_args)
		free_3d_tab(lst->cmd_args);
	close(lst->fd_in);
	close(lst->fd_out);
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
	paths = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			path = ft_strtrim(env[i], "PATH=");
		i++;
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
