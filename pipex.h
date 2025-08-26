/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:26:58 by amine             #+#    #+#             */
/*   Updated: 2025/08/11 12:26:59 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX
#define PIPEX

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "./libft/libft.h"

typedef struct s_pipe
{
	pid_t	pid1;
	pid_t	pid2;
	int	pipefd[2];
	int	infile;
	int	outfile;
	char *path1;
	char *path2;
	char **cmd_args1;
	char **cmd_args2;
}			t_pipe;

void	ft_wait_children(t_pipe *pipe);
void	ft_create_pipe(t_pipe *pipe, char **argv, int argc);
char	*ft_get_full_path(char *cmd, char **envp);
void	ft_child1(t_pipe *pipex, char **envp);
void	ft_child2(t_pipe *pipex, char **envp);
void	ft_error(const char *str);
void	ft_init_pipex(t_pipe *pipex);

#endif