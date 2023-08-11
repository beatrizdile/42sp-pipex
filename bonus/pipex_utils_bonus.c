/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bedos-sa <bedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:27:48 by bedos-sa          #+#    #+#             */
/*   Updated: 2023/08/11 18:27:21 by bedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

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

int	open_fds(t_args *args)
{
	int	fd;

	if (args->i == 2)
		fd = open("input.txt", O_RDWR);
	else if (args->i == args->argc - 2)
		fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (errno != 0)
	{
		free_str_arrs(args->arr);
		perror("pipex");
		exit(errno);
	}
	return (fd);
}

void	try_paths(t_args *args)
{
	int		i;
	int		strlen;
	char	*copy;
	char	**e_arr;

	i = 0;
	while (args->arr[i])
	{
		e_arr = ft_split(args->argv[args->i], ' ');
		strlen = ft_strlen(args->arr[i]) + ft_strlen(e_arr[0]) + 2;
		copy = ft_calloc(strlen, sizeof(char));
		ft_strlcat(copy, args->arr[i], strlen);
		ft_strlcat(copy, "/", strlen);
		ft_strlcat(copy, e_arr[0], strlen);
		if (access(copy, F_OK) == 0)	
			execve(copy, e_arr, args->env);
		free_str_arrs(e_arr);
		free(copy);
		i++;
	}
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