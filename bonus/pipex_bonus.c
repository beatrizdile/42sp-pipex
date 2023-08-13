/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/13 15:01:38 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_args	args;

	if (argc >= 5)
	{
		args.argc = argc;
		args.argv = argv;
		args.env = env;
		args.i = 2;
		pipe(args.pipis);
		pipe(args.pipes);
		commands_fork(&args);
		close_pipes(&args);
	}
	return (0);
}

void	here_doc(t_args	*args)
{
	char	str[100000];

	if (ft_strncmp(args->argv[1], "here_doc", 9) == 0)
	{
		while (1)
		{
			ft_bzero(&str, 100000);
			read(0, str, 100000);
			if (ft_strncmp(str, args->argv[2], ft_strlen(args->argv[2])) == 0 \
				&& ft_strlen(str) == ft_strlen(args->argv[2]) + 1)
				break ;
			ft_putstr_fd(str, args->pipis[1]);
		}
		args->i++;
	}
}

void	commands_fork(t_args *args)
{
	pid_t	pid;

	here_doc(args);
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
			ft_putstr_fd("pipex: command not found\n", 2);
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


//path absoluto