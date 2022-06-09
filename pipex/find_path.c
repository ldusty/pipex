/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by ldusty            #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_cmd(char *s, char **cmd)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	free_paths(cmd);
	exit(EXIT_FAILURE);
}

char	*find_path_strjoin(char **paths, int i, char **cmd)
{
	char	*part_path;
	char	*path;

	part_path = ft_strjoin(paths[i], "/");
	if (!part_path)
		return (NULL);
	path = ft_strjoin(part_path, cmd[0]);
	if (!path)
		return (NULL);
	free(part_path);
	return (path);
}

char	**ft_find_path_utils(char **envp, char **cmd)
{
	int		i;
	char	**paths;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	}
	if (!envp[i] && check_access(cmd[0]) == 1)
	{
		paths = find_cmd(envp);
		return (paths);
	}
	else if (!envp[i] && !check_access(cmd[0]))
		error_cmd("command not found: ", cmd);
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*find_path(char **cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	paths = ft_find_path_utils(envp, cmd);
	if (!paths)
		error_cmd("command not found: ", cmd);
	i = -1;
	while (paths[++i])
	{
		path = find_path_strjoin(paths, i, cmd);
		if (!access(path, F_OK))
		{
			free_paths(paths);
			return (path);
		}
		else
			free(path);
	}
	if (!paths[i])
	{
		free_paths(paths);
		error_cmd("command not found: ", cmd);
	}
	return (0);
}
