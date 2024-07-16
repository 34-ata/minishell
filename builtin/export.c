/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:12 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/15 13:28:33 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	is_valid2(char *arg, int control)
{
	int	i;

	i = -1;
	if ((ft_isdigit(arg[0]) || !ft_isalpha(arg[0])) && arg[0] != '_')
	{
		if (control == 1)
		{
			g_globals_exit = 1;
			return ;
		}
	}
	while (arg[++i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			if (control == 1)
				g_globals_exit = 1;
			return ;
		}
	}
	g_globals_exit = 0;
}

int	check_same(char **envr, char *str)
{
	char	*part;
	int		i;

	i = 0;
	while (envr[i])
	{
		part = ft_substr(envr[i], 0, ft_strlen(envr[i]) \
			- ft_strlen(ft_strchr(envr[i], '=') + 1));
		if (ft_strncmp(part, str, ft_strlen(part)) == 0)
		{
			free(envr[i]);
			envr[i] = ft_strdup(str);
			free(part);
			return (1);
		}
		free(part);
		i++;
	}
	return (0);
}

int	count_args(t_cmds *cmds)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (cmds->args[i])
	{
		if (is_valid(cmds->args[i], 0) == 0)
		{
			check_same(cmds->envr, cmds->args[i]);
			count += 1;
		}
		i++;
	}
	return (count);
}

void	envcpy(char **new_envr, char **s, t_cmds *cmds, int size)
{
	int	i;

	i = 0;
	new_envr = malloc(sizeof(char *) * (size + 2));
	if (!new_envr)
		perror("Malloc!\n");
	while (s[i])
	{
		new_envr[i] = ft_strdup(s[i]);
		i++;
	}
	new_envr[i] = NULL;
	freecpointer(cmds->env->envr);
	cmds->env->envr = new_envr;
}

void	new_envr(t_cmds *cmds, int i, int j, int size)
{
	char	**new_envr;

	size = take_env_size(cmds->envr) + count_args(cmds);
	if (cmds->pid == 0)
		return ;
	new_envr = ft_calloc((size + 1), sizeof(char *));
	new_envr[size] = NULL;
	if (!new_envr)
		perror("Malloc!\n");
	while (cmds->envr[++i])
		new_envr[i] = ft_strdup(cmds->envr[i]);
	while (cmds->args[++j])
		if (is_valid(cmds->args[j], 1) == 0)
			if (check_same(cmds->envr, cmds->args[j]) == 0
				&& check_same(new_envr, cmds->args[j]) == 0)
				new_envr[i++] = ft_strdup(cmds->args[j]);
	j = -1;
	while (cmds->args[++j])
		is_valid2(cmds->args[j], 1);
	freecpointer(cmds->envr);
	cmds->envr = new_envr;
	if (!cmds->next)
		envcpy(NULL, new_envr, cmds, size);
}
