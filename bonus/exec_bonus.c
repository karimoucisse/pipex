/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:02:41 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:16:06 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../Libft/libft.h"
#include "../gnl/get_next_line.h"

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

int	file_close(t_px_list *lst, int fd1, int fd2, int bool)
{
	close(fd1);
	close(fd2);
	close(lst->fd_in);
	close(lst->fd_out);
	if (bool)
		ft_free_lst(lst);
	return (0);
}

int	exec_child_process(t_px_list *lst, int fd_in, int *fd, int i)
{
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		file_close(lst, fd[0], fd[1], 1);
		exit(127);
	}
	close(fd_in);
	if (i < lst->nbr_cmds - 1)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(file_close(lst, fd[0], fd[1], 1));
	}
	else
	{
		if (dup2(lst->fd_out, STDOUT_FILENO) == -1)
			exit(file_close(lst, fd[0], fd[1], 1));
	}
	file_close(lst, fd[0], fd[1], 0);
	execve(lst->cmd_paths[i], lst->cmd_args[i], lst->env);
	ft_free_lst(lst);
	exit(EXIT_FAILURE);
}

int	pipe_exec(t_px_list *lst, int fd_in, int i)
{
	int		fd[2];
	pid_t	pid;
	int		error;

	if (pipe(fd) == -1)
	{
		perror("Pipe");
		return (0);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		return (0);
	}
	if (pid == 0)
		exec_child_process(lst, fd_in, fd, i);
	waitpid(pid, &error, 0);
	print_error("command not found: ", error, lst->cmd_args[i]);
	close(fd[1]);
	close(fd_in);
	return (fd[0]);
}

int	ft_exec(t_px_list *lst)
{
	int	fd_in;
	int	i;

	i = 0;
	fd_in = dup(lst->fd_in);
	close(lst->fd_in);
	while (i < lst->nbr_cmds)
	{
		fd_in = pipe_exec(lst, fd_in, i);
		if (fd_in == 0)
			return (0);
		i++;
	}
	dup2(lst->fd_out, STDOUT_FILENO);
	close(lst->fd_out);
	close(fd_in);
	return (1);
}
