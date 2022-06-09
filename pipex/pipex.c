/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldusty <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by ldusty            #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by ldusty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_proc(char **argv, char **envp, int *fd)
{
	int		filein;

	filein = open(argv[1], O_RDONLY, 0777);
	if (filein == -1)
		error("open filein in child failed");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		error("dup2 failed1");
	if (dup2(filein, STDIN_FILENO) == -1)
		error("dup2 failed2");
	close(fd[0]);
	close(fd[1]);
	close(filein);
	execute(argv[2], envp);
}

void	parent_proc(char **argv, char **envp, int *fd)
{
	int		fileout;

	fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error("open fileout in parent failed");
	if (dup2(fd[0], STDIN_FILENO) == -1)
		error("dup2 failed3");
	if (dup2(fileout, STDOUT_FILENO) == -1)
		error("dup2 failed4");
	close(fd[1]);
	close(fd[0]);
	close(fileout);
	execute(argv[3], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid;

	if (argc == 5)
	{
		if (pipe(fd) == -1)
			error("pipe failed");
		pid = fork();
		if (pid == -1)
			error("fork failed");
		if (pid == 0)
			child_proc(argv, envp, fd);
		parent_proc(argv, envp, fd);
		close(fd[0]);
		close(fd[1]);
	}
	else
		ft_putstr_fd("Bad arguments\n", 2);
	return (0);
}
