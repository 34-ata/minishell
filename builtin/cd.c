/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:43:32 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:13:42 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	setoldpwd(char *oldpwd, char *newpwd, t_cmds *cmd)
{
	int		i;
	char	*newpwd2;

	i = 0;
	setoldpwd2(newpwd, &newpwd2);
	while (cmd->env->envr[i])
	{
		if (ft_strnstr(cmd->env->envr[i], "PWD", 3))
			set_newpwd(newpwd, newpwd2, cmd, i);
		if (ft_strnstr(cmd->env->envr[i], "OLDPWD", 6))
			set_oldpwd(oldpwd, cmd, i);
		i++;
	}
	if (newpwd2 != NULL)
		free(newpwd2);
}

char	*getoldpwd(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->env->envr[i])
	{
		if (ft_strnstr(cmd->env->envr[i], "OLDPWD=", 7))
		{
			return (ft_strdup(ft_strchr(cmd->env->envr[i], '=') + 1));
		}
		i++;
	}
	ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	g_globals_exit = 1;
	return (NULL);
}

char	*gethome(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->env->envr[i])
	{
		if (ft_strnstr(cmd->env->envr[i], "HOME=", 5))
			return (ft_strdup(ft_strchr(cmd->env->envr[i], '=') + 1));
		i++;
	}
	ft_putendl_fd("minishell: cd: HOME not set", 2);
	g_globals_exit = 1;
	return (NULL);
}

int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISREG(path_stat.st_mode));
}

void	cd(t_cmds *cmd, char *newdirect)
{
	char	*oldpwd;
	char	*temppwd;
	char	*newpwd;

	if (newdirect && newdirect[0] == '/')
		newpwd = ft_strdup(newdirect);
	oldpwd = getcwd(NULL, 0);
	if (newdirect && ft_strncmp2(newdirect, "-") == 0 && newdirect[0] != '/')
	{
		if (cd_if(&newpwd, cmd, &newdirect, oldpwd) == 1)
			return ;
	}
	else if (newdirect && newdirect[0] != '/')
		set_newdirect(oldpwd, &temppwd, &newpwd, newdirect);
	if (newdirect == NULL)
		if (cd_if2(&newpwd, cmd, &newdirect, oldpwd) == 1)
			return ;
	if (chdir(newpwd) != 0)
		if (chdir_func(newpwd, newdirect, oldpwd) == 1)
			return ;
	setoldpwd(oldpwd, newpwd, cmd);
	free(oldpwd);
	free(newpwd);
	g_globals_exit = 0;
}
