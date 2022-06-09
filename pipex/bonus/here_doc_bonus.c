/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by ldusty            #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	error_putstr(char *s)
{
	ft_putstr_fd(s, 2);
	exit(EXIT_FAILURE);
}

void	check_argc(int argc)
{
	if (argc < 6)
	{
		ft_putstr_fd("bad arguments\n", 1);
		exit(EXIT_SUCCESS);
	}
}

void	read_input(char *limiter, char *line, int *fd, int reader)
{
	if (reader == 0)
	{
		while (1)
		{
			write(1, "> ", ft_strlen("> "));
			line = get_next_line(0);
			if (line && ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				exit(EXIT_SUCCESS);
			}
			if (line)
				write(fd[1], line, ft_strlen(line));
			else
				error_putstr("find EOF\n");
			free(line);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(reader, NULL, 0);
	}
}

void	here_doc(char *limiter, int argc)
{
	int		reader;
	int		fd[2];
	char	*line;

	line = NULL;
	check_argc(argc);
	if (pipe(fd) == -1)
		error("pipe failed");
	reader = fork();
	if (reader == -1)
		error("fork failed");
	read_input(limiter, line, fd, reader);
}
