/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:42 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/11 18:43:41 by bedos-sa         ###   ########.fr       */
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
	args.arr = find_path(env);
	commands_fork(&args);
	return (0);
}

void	commands_fork(t_args *args)
{

	args->i = 2;
	while (args->i <= args->argc - 2)
	{
		args->pid = fork();
		
		if (args->pid == 0)
		{
			if (args->i == 2)
				first_command(args);
			
			try_paths(args);
			perror("pipex");
			exit(errno);
		}
		args->i++;
	}
	wait(NULL);
	free_str_arrs(args->arr);
}

void	first_command(t_args *args)
{
	int	file_fd;
	file_fd = open_fds(args);
	dup2(file_fd, 0);
}

//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' ./pipex_bonus input.txt "grep 42" "grep sil" "grep bia" output.txt
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' ./pipex_bonus input.txt "grep 42" "pwd" "ls" output.txt
