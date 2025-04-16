/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:32:53 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/02/11 14:49:51 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_com(char *av, char **env, int fd, int *exit_status)
{
	char	*path;
	char	**com_flags;
	int		pid;
	int		pipefd[2];


	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		check_error(dup2(fd, STDIN_FILENO), pipefd[0], pipefd[1]);
		com_flags = ft_split(av, ' ');
		path = findpath(env, com_flags[0]);
		close(fd);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		if (!path)
			command_error(com_flags);
		execve(path, com_flags, NULL);
	}
	close(pipefd[1]);
	close(fd);
	waitpid(-1, exit_status, 0);
	return (pipefd[0]);
}

void	final_process(int fd2, int pipe, char *av, int *exit_status)
{
	char		*path;
	char		**com_flags;
	int			pid;
	extern char	**environ;

	pid = fork();
	if (pid == 0)
	{
		check_error(dup2(pipe, STDIN_FILENO), pipe, fd2);
		com_flags = ft_split(av, ' ');
		path = findpath(environ, com_flags[0]);
		dup2(fd2, STDOUT_FILENO);
		close(pipe);
		close(fd2);
		if (!path)
			command_error(com_flags);
		if (execve(path, com_flags, NULL) == -1)
			exit (2);
	}
	waitpid(-1, exit_status, 0);
	close(pipe);
}

int	main(int ac, char **av, char **env)
{
	int		pipe;
	int		fd1;
	int		fd2;
	int		n;
	int		exit_status;

	if (ac < 5)
		return (ft_putstr_fd("Error\n", 2), 0);
	pipe = 0;
	here_doc(ac, av, env, &exit_status);
	fd1 = open(av[1], O_RDWR);
	file_error(fd1);
	n = 3;
	fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	pipe = execute_com(av[2], env, fd1, &exit_status);
	while ((ac - n) != 2)
	{
		pipe = execute_com(av[n], env, pipe, &exit_status);
		n++;
	}
	final_process(fd2, pipe, av[ac - 2], &exit_status);
	close(fd2);
	exit(WEXITSTATUS(exit_status));
}
