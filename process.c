/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:32:09 by amwahab           #+#    #+#             */
/*   Updated: 2025/08/26 14:41:03 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child1(t_pipe *pipex, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
	{
		// fermer le côté lecture du pipe et le outfile pour cet enfant
		close(pipex->pipefd[0]);
		close(pipex->outfile);

		// rediriger stdin vers infile
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			ft_error("dup2 infile");
		close(pipex->infile);

		// rediriger stdout vers le côté écriture du pipe
		if (dup2(pipex->pipefd[1], STDOUT_FILENO) == -1)
			ft_error("dup2 pipefd[1]");
		close(pipex->pipefd[1]);
		// exécuter la commande
		if (execve(pipex->path1, pipex->cmd_args1, envp) == -1)
		{
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_child2(t_pipe *pipex, char **envp)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
	{
		// fermer le côté écriture du pipe et infile pour cet enfant
		close(pipex->pipefd[1]);
		close(pipex->infile);

		// rediriger stdin vers le côté lecture du pipe
		if (dup2(pipex->pipefd[0], STDIN_FILENO) == -1)
			ft_error("dup2 pipefd[0]");
		close(pipex->pipefd[0]);

		// rediriger stdout vers outfile
		if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
			ft_error("dup2 outfile");
		close(pipex->outfile);
		// exécuter la commande
		if (execve(pipex->path2, pipex->cmd_args2, envp) == -1)
		{
			perror("execve error");
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