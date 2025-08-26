/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:32:09 by amwahab           #+#    #+#             */
/*   Updated: 2025/08/25 20:13:47 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_pipe *pipex, char **argv, char **envp)
{
	pipex->pid1 = fork();
	if(pipex->pid1 == 0)
	{
		close(pipex->pipefd[0]);
		close(pipex->outfile);
		if(dup2(pipex->infile, STDIN_FILENO) == -1)
			ft_error("dup2 infile");
		close(pipex->infile);
		if(dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
			ft_error("dup2 pipefd[1]");
		close(pipex->pipefd[1]);
		pipex->cmd_args = ft_split(argv[2], ' ');
		if(execve(pipex->path1, pipex->cmd_args, envp) == -1)
		{
			perror("execeve error");
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_child2(t_pipe *pipex, char **argv, char **envp)
{
	pipex->pid2 = fork();
	if(pipex->pid2 == 0)
	{
		close(pipex->pipefd[1]);
		close(pipex->infile);
		if(dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
			ft_error("dup2 pipefd[0]");
		close(pipex->pipefd[0]);
		if(dup2(pipex->outfile, STDOUT_FILENO) == -1)
			ft_error("dup2 outfile");
		close(pipex->outfile);
		pipex->cmd_args = ft_split(argv[3], ' ');
		if(execve(pipex->path2, pipex->cmd_args, envp) == -1)
		{
			perror("execeve error");
			exit(EXIT_FAILURE);
		}
	}
}

void ft_wait_children(t_pipe *pipex)
{
    int status;
    waitpid(pipex->pid1, &status, 0);
    waitpid(pipex->pid2, &status, 0);
}