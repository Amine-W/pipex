/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:30:15 by amwahab           #+#    #+#             */
/*   Updated: 2025/08/26 14:49:23 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	pipex;

	// Parsing à faire : vérifier le nombre d'arguments
	if (argc != 5)
		ft_error("Usage: ./pipex infile cmd1 cmd2 outfile");

	// Initialiser la structure pour éviter les erreurs
	ft_init_pipex(&pipex);

	// Récupérer le chemin complet de la première commande
	pipex.cmd_args1 = ft_split(argv[2], ' ');
	pipex.path1 = ft_get_full_path(pipex.cmd_args1[0], envp);
	printf("path1: %s\n", pipex.path1);
	if (!pipex.path1)
	{
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}

	// Récupérer le chemin complet de la deuxième commande
	pipex.cmd_args2 = ft_split(argv[3], ' ');
	pipex.path2 = ft_get_full_path(pipex.cmd_args2[0], envp);
	printf("path2: %s\n", pipex.path2);
	if (!pipex.path2)
	{
		perror(argv[3]);
		exit(EXIT_FAILURE);
	}

	// Créer un canal de communication
	ft_create_pipe(&pipex, argv, argc);

	// Créer le premier processus enfant pour exécuter la première commande
	ft_child1(&pipex, envp);

	// Créer le deuxième processus enfant pour exécuter la deuxième commande
	ft_child2(&pipex, envp);
	
	close(pipex.infile);
	close(pipex.outfile);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	// Attendre que les deux processus enfants aient fini
	ft_wait_children(&pipex);
	
	ft_free_split(pipex.cmd_args1);
	ft_free_split(pipex.cmd_args2);

	return (0);
}