/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:53:14 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:12:59 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pipecheck(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(127);
	}
}

void	fderror(char *output)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(output, 2);
	if (is_directory(output))
	{
		ft_putstr_fd(": Is a directory\n", 2);
		exit(1);
	}
	else if (!is_file(output))
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	else if (access(output, R_OK))
	{
		ft_putstr_fd(": Permission denied\n", 2);
		exit(1);
	}
	g_globals_exit = 1;
	exit(1);
}

void	fderror2(char *output)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(output, 2);
	if (is_directory(output))
		ft_putstr_fd(": Is a directory\n", 2);
	else if (!is_file(output))
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (access(output, R_OK))
		ft_putstr_fd(": Permission denied\n", 2);
	g_globals_exit = 1;
}

void	closedup(int fd[2])
{
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

char	*find_path_while(char **path, char *command)
{
	int		i;
	char	*temp;
	char	*test;

	i = 0;
	while (path[i] && path)
	{
		temp = ft_strjoin(path[i], "/");
		test = ft_strjoin(temp, command);
		if (!access(test, X_OK))
		{
			free(path);
			free(temp);
			return (test);
		}
		free(temp);
		free(test);
		i++;
	}
	return (NULL);
}
