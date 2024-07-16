/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:43:50 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/15 13:47:50 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	search_eq(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	searchh_in_env(char **env, char **args)
{
	char	*temp;
	int		count;
	int		i;
	int		j;

	i = -1;
	count = 0;
	while (env[++i])
	{
		j = -1;
		while (args[++j])
		{
			temp = ft_substr(env[i], 0, search_eq(env[i]));
			if (check_cmmn(temp, args[j]) == 0)
				count++;
			free(temp);
		}
	}
	return (count);
}

int	count_valid(t_cmds *cmds)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*cmds->args && cmds->args[i])
	{
		if (is_valid(cmds->args[i], 1) == 0)
			count += 1;
		i++;
	}
	return (count);
}

static char	**unset_env_while(t_cmds *cmds, int j, int i, int size)
{
	char	**new_envr;
	char	*temp;
	int		k;

	new_envr = malloc(sizeof(char *) * (size + 2));
	while (cmds->envr[i])
	{
		k = -1;
		while (cmds->args[++k] && cmds->envr[i])
		{
			temp = ft_substr(cmds->envr[i], 0, search_eq(cmds->envr[i]));
			if (check_cmmn(temp, cmds->args[k]) == 0)
				i++;
			free (temp);
		}
		if (cmds->envr[i])
			new_envr[j++] = ft_strdup(cmds->envr[i]);
		else
			break ;
		i++;
	}
	new_envr[j] = NULL;
	return (new_envr);
}

void	unset_env(t_cmds *cmds)
{
	char	**new_envr;
	int		size;

	if (!cmds->args[0])
		return ;
	unset_error(cmds);
	if (searchh_in_env(cmds->envr, cmds->args) == 0)
		return ;
	size = (take_env_size(cmds->envr) - searchh_in_env(cmds->envr, cmds->args));
	new_envr = unset_env_while(cmds, 0, 0, size);
	if (!new_envr)
		perror("Malloc!\n");
	freecpointer(cmds->envr);
	cmds->envr = new_envr;
	if (!cmds->next)
		envcpy(NULL, new_envr, cmds, size);
	g_globals_exit = 0;
}
