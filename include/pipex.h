/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 23:49:22 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/09 17:47:18 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

typedef struct args
{
	int		argc;
	int		pid;
	char	**argv;
	char	**env;
}			args;

char		**find_path(char **env);
int			try_paths(char **arr, args args);
void		free_str_arrs(char **arr);
int			open_fds(args args, char **arr);

