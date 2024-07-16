/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:52 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:27:47 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_path(char **env)
{
	char	**ret;
	char	*tmp;
	size_t	i;

	i = 0;
	while (env[i] && env)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			tmp = ft_strchr(env[i], '/');
			if (!tmp)
				tmp = ft_strchr(env[i], '=') + 1;
			ret = ft_split(tmp, ':');
			return (ret);
		}
		i++;
	}
	return (NULL);
}

void	patherror0(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": No such file or directory", 2);
	g_globals_exit = 127;
	exit(127);
}

char	*findpath(char **command, char **env)
{
	char	**path;
	char	*temp;

	if (command[0][0] == '\0')
	{
		patherror0(command[0]);
		return (NULL);
	}
	path = get_path(env);
	if (!path || !path[0])
	{
		if (access(command[0], X_OK))
			patherror0(command[0]);
		else
			execve(command[0], command, env);
	}
	if (path && path[0])
	{
		temp = find_path_while(path, command[0]);
		if (temp != NULL)
			return (temp);
	}
	free(path);
	patherror1(command[0]);
	return (NULL);
}

int	runcommanderror(char **command, int i)
{
	if (i == 0)
	{
		error_write(command[0]);
		ft_putendl_fd(": No such file or directory", 2);
		g_globals_exit = 127;
		return (1);
	}
	else if (i == 1)
	{
		error_write(command[0]);
		ft_putendl_fd(": Permission denied", 2);
		g_globals_exit = 126;
		return (1);
	}
	else if (i == 2)
	{
		error_write(command[0]);
		ft_putendl_fd(": is a directory: ", 2);
		g_globals_exit = 126;
		return (1);
	}
	return (0);
}

int	runcommand(char **command, t_cmds *cmd)
{
	char	*path;

	if (!command[0])
		return (0);
	if (check_cmmn(command[0], "..") == 0)
		if (runcommanderror(command, 0))
			return (1);
	if (ft_strchr(command[0], '/'))
	{
		path = command[0];
		if (is_directory(path))
			if (runcommanderror(command, 2))
				return (1);
		if (!is_file(path))
			if (runcommanderror(command, 0))
				return (1);
		if (access(path, X_OK))
			if (runcommanderror(command, 1))
				return (1);
	}
	else
		path = findpath(command, cmd->envr);
	execve(path, command, cmd->envr);
	return (0);
}
