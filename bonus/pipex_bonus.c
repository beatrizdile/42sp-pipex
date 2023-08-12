/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/12 17:47:17 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_args	args;

	args.argc = argc;
	args.argv = argv;
	args.env = env;
	pipe(args.pipis);
	pipe(args.pipes);
	commands_fork(&args);
	close_pipes(&args);
	return (0);
}

void	commands_fork(t_args *args)
{
	pid_t	pid;

	args->i = 2;
	while (args->i <= args->argc - 2)
	{
		pid = fork();
		if (pid == 0)
		{
			args->arr = find_path(args->env);
			if (args->i == 2)
				first_command(args);
			else if (args->i == args->argc - 2)
				last_command(args);
			else
				middle_command(args);
			close_pipes(args);
			try_paths(args);
			free_str_arrs(args->arr);
			perror("pipex");
			exit(errno);
		}
		recycle_pipe(args);
		args->i++;
	}
	wait(NULL);
}

void	close_pipes(t_args *args)
{
	close(args->pipis[0]);
	close(args->pipis[1]);
	close(args->pipes[0]);
	close(args->pipes[1]);
}
