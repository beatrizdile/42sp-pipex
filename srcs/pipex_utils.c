/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:27:48 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/13 16:18:39 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	exec_process(int pid, char **arr, int *pipis, t_args args)
{
	int		file_id;

	if (pid == 0)
	{
		args.pid = 2;
		file_id = open_fds(args, arr);
		dup2(file_id, 0);
		dup2(pipis[1], 1);
		close(pipis[0]);
		try_paths(arr, args);
	}
	else
	{
		args.pid = 3;
		file_id = open_fds(args, arr);
		dup2(pipis[0], 0);
		dup2(file_id, 1);
		close(pipis[1]);
		try_paths(arr, args);
	}
}

char	**find_path(char **env)
{
	char	*start;
	char	**arr;

	arr = NULL;
	while (*env)
	{
		start = ft_strnstr(*env, "PATH=", 5);
		if (start != NULL)
		{
			start = ft_strtrim(start, "PATH=");
			arr = ft_split(start, ':');
			break ;
		}
		env++;
	}
	free(start);
	return (arr);
}

int	open_fds(t_args args, char **arr)
{
	int	fd;
	int	i;

	if (args.pid == 2)
	{
		i = 1;
		fd = open(args.argv[i], O_RDWR);
	}
	else
	{
		i = args.argc - 1;
		fd = open(args.argv[i], O_RDWR | O_CREAT | O_TRUNC, 0777);
	}
	if (errno != 0)
	{
		free_str_arrs(arr);
		perror("pipex");
		exit(errno);
	}
	return (fd);
}

int	try_paths(char **arr, t_args args)
{
	int		i;
	int		strlen;
	char	*copy;
	char	**e_arr;

	i = 0;
	while (arr[i])
	{
		strlen = ft_strlen(arr[i]) + ft_strlen(args.argv[args.pid]) + 2;
		e_arr = ft_split(args.argv[args.pid], ' ');
		copy = ft_calloc(strlen, sizeof(char));
		ft_strlcat(copy, arr[i], strlen);
		ft_strlcat(copy, "/", strlen);
		ft_strlcat(copy, e_arr[0], strlen);
		execve(copy, e_arr, args.env);
		free_str_arrs(e_arr);
		free(copy);
		i++;
	}
	free_str_arrs(arr);
	perror("pipex");
	return (0);
}

void	free_str_arrs(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}
