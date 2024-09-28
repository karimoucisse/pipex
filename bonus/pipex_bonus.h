/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcisse <kcisse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:01:25 by kcisse            #+#    #+#             */
/*   Updated: 2024/09/28 14:00:34 by kcisse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct t_px_list
{
	int					fd_in;
	int					fd_out;
	char				*limiter;
	int					is_infile;
	int					is_heredoc;
	char				**cmd_paths;
	char				***cmd_args;
	int					nbr_cmds;
	char				**env;
}t_px_list;

// MAIN
void		ft_check_args(int ac, char **av, char **env);
int			ft_handle_cmd_paths(char **av, t_px_list *lst, char **pt, char *tp);
void		handle_error_msg(char *error_msg);
void		ft_write_pipe(int arg_nbr);

// HANDLE_STRUCT
t_px_list	*lst_new(void);
char		***ft_fill_cmd_args(char **av, int nbr_cmd);
char		**ft_fill_cmd_paths(char **av, t_px_list *lst);
t_px_list	*ft_fill_lst(char **av, int ac, char **env);
int			ft_here_doc(t_px_list *lst);

// EXEC
int			ft_exec(t_px_list *lst);
int			pipe_exec(t_px_list *lst, int fd_in, int i);
int			exec_child_process(t_px_list *lst, int fd_in, int *fd, int i);
int			file_close(t_px_list *lst, int fd1, int fd2, int bool);
void		print_error(char *str, int error, char **arg);

// UTILS
void		ft_free_tab(char **tab);
int			ft_free_lst(t_px_list *lst);
void		free_3d_tab(char ***tab);
char		*get_cmd_path(char *cmd, char **env);
char		*ft_find_path(char **paths, char *cmd_l);
#endif
