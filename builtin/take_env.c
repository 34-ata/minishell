/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:43:45 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/15 12:06:50 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	take_env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i] != NULL)
		i++;
	return (i);
}

void	take_env(t_cmds *cmds, t_main_env *env, int status, char **environ)
{
	int	i;

	i = -1;
	if (status == 0)
	{
		env->envr = malloc(sizeof(char *) * (take_env_size(environ) + 1));
		if (!env->envr)
			perror("Malloc!\n");
		while (++i < take_env_size(environ))
			env->envr[i] = ft_strdup(environ[i]);
		env->envr[i] = NULL;
	}
	else
	{
		cmds->envr = malloc(sizeof(char *) * (take_env_size(env->envr) + 1));
		if (!cmds->envr)
			perror("Malloc!\n");
		while (++i < take_env_size(env->envr))
			cmds->envr[i] = ft_strdup(env->envr[i]);
		cmds->envr[i] = NULL;
	}
}

void	print_env(t_cmds *cmds, int status)
{
	int	i;

	i = 0;
	while (cmds->env->envr[i])
	{
		if (status == 1)
			printf("declare -x ");
		printf("%s\n", cmds->env->envr[i]);
		i++;
	}
	g_globals_exit = 0;
}
