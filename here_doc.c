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
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 && *(line + ft_strlen(delimiter)) == '\n')
		{
			free (line);
			break ;
		}
		write(fd2, line, ft_strlen(line));
		free (line);
	}
}

void	here_doc(int ac, char **av, char **env, int *exit_status)
{
	int		pipe;
	int		fd1;
	int		fd2;
	int		n;

	if (ft_strncmp(av[1], "here_doc", 9) != 0)
		return ;
	if (ac < 6)
	{
		ft_putstr_fd("Error\n", 2);
		exit (1);
	}
	fd1 = open("temp.txt", O_CREAT | O_RDWR, 0644);
	n = 4;
	write_on_file(fd1, av[2]);
	close(fd1);
	fd1 = open("temp.txt", O_RDWR);
	pipe = execute_com(av[3], env, fd1, exit_status);
	while ((ac - n) != 2)
	{
		pipe = execute_com(av[n], env, pipe, exit_status);
		n++;
	}
	fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0777);
	final_process(fd2, pipe, av[ac - 2], exit_status);
	unlink ("temp.txt");
	exit (*exit_status);
}
