/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:27:06 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/27 22:04:19 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct t_px_list
{
	int		fd_in;
	int		fd_out;
	int		is_infile;
	char	**cmd_paths;
	char	***cmd_args;
}t_px_list;

// MAIN
void		ft_check_args(int ac, char **av, char **env);

// HANDLE_STRUCT
t_px_list	*lst_new(void);
char		***ft_fill_cmd_args(char **av);
char		**ft_fill_cmd_paths(char **av, char **env);
t_px_list	*ft_fill_lst(char **av, int ac, char **env);
int			ft_handle_cmd_paths(char **av, char **env, char **pth_tb, char *tp);

// EXEC
int			ft_exec(t_px_list *lst, char **env);
int			ft_pid1(t_px_list *lst, char **env, int *fd, pid_t *pid2);
int			ft_pid2(t_px_list *lst, char **env, int *fd, pid_t *pid2);

// UTILS
int			ft_free_tab(char **tab);
int			ft_free_lst(t_px_list *lst);
void		free_3d_tab(char ***tab);
char		*get_cmd_path(char *cmd, char **env);
char		*ft_find_path(char **paths, char *cmd_l);
#endif
