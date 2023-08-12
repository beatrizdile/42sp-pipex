/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/12 16:00:48 by bedos-sa         ###   ########.fr       */
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
		if (args->i < args->argc - 2)
			recycle_pipe(args);
		args->i++;
	}
	wait(NULL);
}

void	first_command(t_args *args)
{
	int	file_fd;
	file_fd = open_fds(args);
	dup2(file_fd, 0);
	dup2(args->pipis[1], 1);
	close(file_fd);
}

void	middle_command(t_args *args)
{
	if (args->i % 2 == 0)
	{
		dup2(args->pipes[0], 0);
		dup2(args->pipis[1], 1);
	}
	else
	{
		dup2(args->pipis[0], 0);
		dup2(args->pipes[1], 1);
	}
}

void	last_command(t_args *args)
{
	int	file_fd;
	file_fd = open_fds(args);
	if (args->i % 2 == 0)
		dup2(args->pipes[0], 0);
	else
		dup2(args->pipis[0], 0);
	dup2(file_fd, 1);
	close(file_fd);
}

void	close_pipes(t_args *args)
{
	close(args->pipis[0]);
	close(args->pipis[1]);
	close(args->pipes[0]);
	close(args->pipes[1]);
}

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' ./pipex_bonus input.txt "grep 42" "grep sil" "grep bia" output.txt
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' ./pipex_bonus input.txt "grep 42" "pwd" "ls" output.txt
