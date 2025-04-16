/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldei-sva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:32:03 by ldei-sva          #+#    #+#             */
/*   Updated: 2025/02/07 16:32:06 by ldei-sva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**look_for_path(char **env)
{
	char	**paths;

	while (*env)
	{
		if (ft_strnstr(*env, "PATH", 4) != NULL)
		{
			paths = ft_split(*(env) + 5, ':');
			return (paths);
		}
		env++;
	}
	return (NULL);
}

char	*look_for_rightpath(char **paths, char *com)
{
	int		n;
	char	*temp;
	char	*path;

	n = 0;
	while (paths[n])
	{
		temp = ft_strjoin(paths[n], "/");
		path = ft_strjoin(temp, com);
		free(temp);
		if (access(path, F_OK) == 0)
			return (path);
		else
			free(path);
		n++;
	}
	return (NULL);
}

char	*findpath(char **env, char *com)
{
	char	**paths;
	char	*right_path;

	paths = look_for_path(env);
	right_path = look_for_rightpath(paths, com);
	free_array(paths);
	return (right_path);
}
