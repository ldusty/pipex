/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by ldusty            #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_access(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (1);
	return (0);
}

char	**find_cmd(char **envp)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	paths = ft_split(envp[i], '=');
	if (!paths)
		return (NULL);
	return (paths);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	while (i > 0)
	{
		free(paths[i - 1]);
		i--;
	}
	free(paths);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
		error("split failed");
	path = find_path(cmd, envp);
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		free_paths(cmd);
		error("execve failed");
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
