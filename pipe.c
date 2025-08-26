/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:35:51 by amwahab           #+#    #+#             */
/*   Updated: 2025/08/26 13:37:55 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init_pipex(t_pipe *pipex)
{
	pipex->pipefd[0] = 0;
	pipex->pipefd[1] = 0;
	pipex->pid1 = 0;
	pipex->pid2 = 0;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->path1 = NULL;
	pipex->path2 = NULL;
}
void	ft_create_pipe(t_pipe *pipex, char **argv, int argc)
{
	//le but ici est de stocker les fd du infile et du outfile
	pipex->infile = open(argv[1], O_RDONLY);
	if(pipex->infile == -1)
		ft_error("infile error");
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(pipex->outfile == -1)
		ft_error("outfile error");
	//Ici on crée un canal de communication, il nous servira plus tard pour que nos 2 processus enfatns puissent communiquer entre eux
	if(pipe(pipex->pipefd) == -1)
	{
		perror("pipe fail");
		close(pipex->infile);
		close(pipex->outfile);
		exit(1);
	}
}

void	ft_error(const char *str)
{
	perror(str);
	exit(1);
}