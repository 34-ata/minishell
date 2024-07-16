/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:44:08 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:46:25 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_oldpwd(char *oldpwd, t_cmds *cmd, int i)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", oldpwd);
	free(cmd->env->envr[i]);
	cmd->env->envr[i] = tmp;
}

void	set_newpwd(char *newpwd, char *newpwd2, t_cmds *cmd, int i)
{
	char	*tmp;

	if (newpwd2 == NULL)
		tmp = ft_strjoin("PWD=", newpwd);
	else
		tmp = ft_strjoin("PWD=", newpwd2);
	free(cmd->env->envr[i]);
	cmd->env->envr[i] = tmp;
}

void	exit_error_2(t_cmds *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->flags[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_globals_exit = 255;
	exit (255);
}

t_main_env	*set_env_main(char **av)
{
	t_main_env	*env;

	env = malloc(sizeof(t_main_env));
	env->minipwd = set_dollar_zero(av, 0);
	return (env);
}
