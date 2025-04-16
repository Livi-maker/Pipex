/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:41:57 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/02/07 16:43:02 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file_error(int n)
{
	if (n == -1)
	{
		perror ("Error");
		return (0);
	}
	return (1);
}

void	command_error(char	**com_flags)
{
	free_array(com_flags);
	ft_putstr_fd("Command not found\n", 2);
	exit(127);
}

void	check_error(int n, int fd, int fd2)
{
	if (n == -1)
	{
		close(fd);
		close(fd2);
		exit(1);
	}
}
