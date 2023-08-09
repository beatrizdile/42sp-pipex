#include "libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pid;
	char	**arr;
	args	args;

	args.argc = argc;
	args.argv = argv;
	args.env = env;
	// int	fd[2];
	if (argc != 5)
		exit(1);
	// if (pipe(fd) == -1)
	// {
	// 	perror("pipex");
	// 	exit(errno);
	// }
	arr = find_path(env);
	pid = fork();
	if (pid == -1)
	{
		perror("pipex");
		exit(errno);
	}
	if (pid == 0)
	{
		args.pid = 0;
		try_paths(arr, args);
	}
	else
	{
		wait(NULL);
		args.pid = 1;
		try_paths(arr, args);
		free_paths(arr);
	}
	return (0);
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

void	free_paths(char **arr)
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

int	try_paths(char **arr, args args)
{
	int		i;
	int		strlen;
	char	*copy;
	char	**e_arr;

	i = 0;
	while (arr[i])
	{
		strlen = ft_strlen(arr[i]) + ft_strlen(args.argv[2]) + 2;
		copy = ft_calloc(strlen, sizeof(char));
		ft_strlcat(copy, arr[i], strlen);
		ft_strlcat(copy, "/", strlen);

		ft_strlcat(copy, args.argv[2], strlen);
		ft_printf("%s\n", copy);
		e_arr = ft_split(args.argv[2], ' ');
		execve(copy, e_arr, args.env);
		free(e_arr);
		free(copy);
		i++;
	}
	free_paths(arr);
	perror("pipex");
	return (0);
}


// adicionar flags
// mudar entrada e saida padrão
// input e output de arquivo
// valgrind --leak-check=full --leak-check=full --show-leak-kinds=all --trace-children=yes --trace-children-skip=*/bin/* ./pipex input.txt ls pwd output.txt