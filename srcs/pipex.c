/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/10 10:46:28 by bedos-sa         ###   ########.fr       */
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
	if (pid == 0)
		exec_process(0, arr, pipis, args);
	else
		exec_process(1, arr, pipis, args);
	wait(NULL);
	return (0);
}
