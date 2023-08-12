/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dups.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 16:11:34 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/12 18:11:49 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

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
