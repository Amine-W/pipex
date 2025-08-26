/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:59:55 by amwahab           #+#    #+#             */
/*   Updated: 2025/08/26 13:24:07 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

char	*ft_get_full_path(char *cmd, char **envp)
{
	int		i;
	char	*path = NULL;
	char	**paths;
	char	*full_path;
	char	*tmp;

	i = 0;
	if (!cmd || !envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	printf("path: %s\n", path);
	if (!envp[i])
		return (NULL);
	paths = ft_split(path, ':');
	/*i = 0;
	while(paths[i])
	{
		printf("paths: %s\n", paths[i]);
		i++;
	}*/
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}