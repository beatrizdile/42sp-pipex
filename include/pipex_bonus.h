/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:49:22 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/11 21:04:37 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct t_args
{
	int		i;
	int		argc;
	int		pid;
	int		last_pi;
	int		pipis[2];
	int		pipes[2];
	char	**arr;
	char	**argv;
	char	**env;
}			t_args;

char		**find_path(char **env);
void		try_paths(t_args *t_args);
void		free_str_arrs(char **arr);
int			open_fds(t_args *t_args);
void		commands_fork(t_args *args);
void		first_command(t_args *args);
void		middle_command(t_args *args);
void		last_command(t_args *args);
void		close_pipes(t_args *args);

#endif