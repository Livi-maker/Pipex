/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:30:38 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/02/07 16:30:40 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <errno.h>
# include <string.h>

char	*findpath(char **env, char *com);
void	here_doc(int ac, char **av, char **env, int *exit_status);
void	write_on_file(int fd2, char *delimiter);
int		execute_com(char *av, char **env, int fd, int *exit_status);
void	final_process(int fd2, int pipe, char *av, int *exit_status);
void	check_error(int n, int fd, int fd2);
void	command_error(char **com_flags);
void	free_array(char **array);
int		file_error(int n);

#endif
