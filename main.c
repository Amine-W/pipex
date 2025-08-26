/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:30:15 by amwahab           #+#    #+#             */
/*   Updated: 2025/08/26 13:36:05 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;
	
	//parsing à faire
	if (argc != 5)
		ft_error("Usage: ./pipex infile cmd1 cmd2 outfile");
	//initialiser la strucutre permet d'éviter les erreurs et d'avoir une strucutre propre prête à l'emploi
	ft_init_pipex(&pipex);
	//fonction pour récupérer le chemin à exec
	pipex.path1 = ft_get_full_path(argv[2], envp);
	printf("path1: %s", pipex.path1);
	if (!pipex.path1)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	pipex.path2 = ft_get_full_path(argv[3], envp);
	printf("path2: %s", pipex.path2);
	if (!pipex.path2)
	{
		printf("fail");
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	//ici nous créons un canal de commmunication , pour le moment il ne nous sert à rien mais nous allons nous en servir pour communiquer entre les 2 processus enfants
	ft_create_pipe(&pipex, argv, argc);
	// une fois cela fait, nous devons nous occuper de la première commande, pour cela nous devons créer une nouveau processus car si nous executons la commande dans le main, alors son image sera écraséé
	ft_child1(&pipex, argv, envp);
	ft_child2(&pipex, argv, envp);;
	//enfin attendons que les 2 processus est finis, pour cela utilise waitpid
	ft_wait_children(&pipex);
}