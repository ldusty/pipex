/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by ldusty            #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 1)
		file = open(argv, O_RDONLY, 0777);
	else if (i == 2)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		error("open failed");
	return (file);
}

void	child_proc(char *argv, char **envp)
{
	int	pid;
	int	fd[2];

	if (pipe(fd) == -1)
		error("pipe failed");
	pid = fork();
	if (pid == -1)
		error("fork failed");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	if_in_main(char **argv, int argc, int *filein, int *fileout)
{
	int	i;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		here_doc(argv[2], argc);
		*fileout = open_file(argv[argc - 1], 0);
	}
	else
	{
		i = 2;
		*filein = open_file(argv[1], 1);
		*fileout = open_file(argv[argc - 1], 2);
		if (dup2(*filein, STDIN_FILENO) == -1)
			error("dup2 failed");
	}
	return (i);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	filein = 0;
	fileout = 0;
	if (argc >= 5)
	{
		i = if_in_main(argv, argc, &filein, &fileout);
		while (i < argc - 2)
			child_proc(argv[i++], envp);
		if (dup2(fileout, STDOUT_FILENO) == -1)
			error("dup2 failed");
		execute(argv[argc - 2], envp);
	}
	else
		ft_putstr_fd("Bad arguments\n", 2);
	return (0);
}
