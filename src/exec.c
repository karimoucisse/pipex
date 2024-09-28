/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:33:21 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../Libft/libft.h"

void	print_error(char *str, int error, char **arg)
{
	int		i;

	i = 0;
	if (error == 256 || error == 127)
	{
		write(2, str, ft_strlen(str));
		while (arg[i])
		{
			write(2, arg[i], ft_strlen(arg[i]));
			i++;
		}
		write(2, "\n", 1);
	}
	else if (error != 0)
		perror("exec");
}

int	ft_find_space(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_strchr(" \n\t\v\f\r", str[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_pid1(t_px_list *lst, char **env, int *fd, pid_t *pid1)
{
	*pid1 = fork();
	if (*pid1 == -1)
	{
		perror("Fork");
		return (0);
	}
	if (*pid1 == 0)
	{
		close(fd[0]);
		if (dup2(lst->fd_in, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(ft_free_lst(lst));
		close(fd[1]);
		close(lst->fd_in);
		if (ft_find_space(lst->cmd_args[0]))
			exit(ft_free_lst(lst));
		execve(lst->cmd_paths[0], lst->cmd_args[0], env);
		exit(ft_free_lst(lst));
	}
	return (1);
}

int	ft_pid2(t_px_list *lst, char **env, int *fd, pid_t *pid2)
{
	*pid2 = fork();
	if (*pid2 == -1)
	{
		perror("Fork");
		return (0);
	}
	if (*pid2 == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(ft_free_lst(lst));
		if (dup2(lst->fd_out, STDOUT_FILENO) == -1)
			exit(ft_free_lst(lst));
		close(fd[0]);
		close(fd[1]);
		if (ft_find_space(lst->cmd_args[1]))
			exit(ft_free_lst(lst));
		execve(lst->cmd_paths[1], lst->cmd_args[1], env);
		exit(ft_free_lst(lst));
	}
	return (1);
}

int	ft_exec(t_px_list *lst, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		return_val;
	int		error;

	return_val = 1;
	if (pipe(fd) == -1)
	{
		perror("Pipe");
		return (0);
	}
	if (!ft_pid1(lst, env, fd, &pid1))
		return_val = 0;
	if (!ft_pid2(lst, env, fd, &pid2))
		return_val = 0;
	close(fd[1]);
	close(fd[0]);
	waitpid(pid1, &error, 0);
	print_error("command not found: ", error, lst->cmd_args[0]);
	waitpid(pid2, &error, 0);
	print_error("command not found: ", error, lst->cmd_args[1]);
	return (return_val);
}
