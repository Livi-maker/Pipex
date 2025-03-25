/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:31:07 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/02/07 16:31:09 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	write_on_file(int fd2, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
			return ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free (line);
			break ;
		}
		write(fd2, line, ft_strlen(line));
		free (line);
	}
}

void	here_doc(int ac, char **av, char **env)
{
	int		pipe;
	int		fd1;
	int		fd2;
	int		n;

	if (ft_strncmp(av[1], "here_doc", 9) != 0)
		return ;
	fd1 = open("temp.txt", O_CREAT | O_RDWR, 0644);
	check_errors(fd1);
	n = 4;
	write_on_file(fd1, av[2]);
	close(fd1);
	fd1 = open("temp.txt", O_RDWR);
	check_errors(fd1);
	pipe = execute_com(av[3], env, fd1);
	while ((ac - n) != 2)
	{
		pipe = execute_com(av[n], env, pipe);
		n++;
	}
	fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0777);
	check_errors(fd2);
	final_process(fd2, pipe, av[ac - 2], env);
	check_errors(unlink ("temp.txt"));
	exit (0);
}
