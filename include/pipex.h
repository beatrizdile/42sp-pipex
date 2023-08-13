/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:49:22 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/13 16:20:41 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

typedef struct t_args
{
	int		argc;
	int		pid;
	char	**arr;
	char	**argv;
	char	**env;
	char	**pipis;
}			t_args;

char		**find_path(char **env);
int			try_paths(char **arr, t_args t_args);
void		free_str_arrs(char **arr);
int			open_fds(t_args t_args, char **arr);
void		exec_process(int pid, char **arr, int *pipis, t_args args);
void		processes(int pid, char **arr, int *pipis, t_args *args);

#endif