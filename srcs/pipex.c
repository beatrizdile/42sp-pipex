/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/13 16:28:22 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pid;
	int		pipis[2];
	char	**arr;
	t_args	args;

	if (argc != 5)
		exit(1);
	if (pipe(pipis) == -1)
	{
		perror("pipex");
		exit(errno);
	}
	args.argc = argc;
	args.argv = argv;
	args.env = env;
	arr = find_path(env);
	pid = fork();
	processes(pid, arr, pipis, &args);
	return (0);
}

void	processes(int pid, char **arr, int *pipis, t_args *args)
{
	char	**e_arr;

	if (pid == 0)
	{
		e_arr = ft_split(args->argv[0], ' ');
		if (access(e_arr[0], F_OK) == 0)
			execve(e_arr[0], e_arr, args->env);
		free_str_arrs(e_arr);
		exec_process(0, arr, pipis, *args);
	}
	else
	{
		e_arr = ft_split(args->argv[1], ' ');
		if (access(e_arr[0], F_OK) == 0)
			execve(e_arr[0], e_arr, args->env);
		free_str_arrs(e_arr);
		exec_process(1, arr, pipis, *args);
	}
	wait(NULL);
}
