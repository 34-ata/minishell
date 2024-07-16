/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:52 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:13:07 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	chdir_func(char *newpwd, char *newdirect, char *oldpwd)
{
	if (is_file(newpwd))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(newdirect, 2);
		ft_putstr_fd(": not a directory\n", 2);
	}
	else if (!is_directory(newpwd))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(newdirect, 2);
		ft_putstr_fd(": no such file or directory\n", 2);
	}
	else if (access(newpwd, X_OK))
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(newdirect, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	free(newpwd);
	free(oldpwd);
	g_globals_exit = 1;
	return (1);
}

void	set_newdirect(char *oldpwd, char **tmppwd, char **newpwd, char *nd)
{
	*tmppwd = ft_strjoin(oldpwd, "/");
	*newpwd = ft_strjoin(*tmppwd, nd);
	free(*tmppwd);
}

int	cd_if(char **newpwd, t_cmds *cmd, char **newdirect, char *oldpwd)
{
	*newpwd = getoldpwd(cmd);
	if (!*newpwd)
	{
		free(oldpwd);
		return (1);
	}
	*newdirect = *newpwd;
	return (0);
}

int	cd_if2(char **newpwd, t_cmds *cmd, char **newdirect, char *oldpwd)
{
	*newpwd = gethome(cmd);
	if (!*newpwd)
	{
		free(oldpwd);
		return (1);
	}
	*newdirect = *newpwd;
	return (0);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
