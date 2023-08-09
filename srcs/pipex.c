#include "libft.h"
#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	int		pid;
	int		pipis[2];
	int		file_id;
	char	**arr;
	args	args;

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
	if (pid == -1)
	{
		perror("pipex");
		exit(errno);
	}
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
	wait(NULL);
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

int	open_fds(args args, char **arr)
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

int	try_paths(char **arr, args args)
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

// mudar entrada e saida padrão
// input e output de arquivo
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' ./pipex input.txt "grep 42" "grep sil" output.txt
