/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:43:32 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 18:52:54 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_built_2(t_cmds *cmds)
{
	if (cmds->cmd && ft_strncmp2(cmds->cmd, "env") == 0
		&& !cmds->args[0])
		print_env(cmds, 0);
	if (cmds->cmd && ft_strncmp2(cmds->cmd, "env") == 0
		&& cmds->args[0])
	{
		write(2, "env: ", ft_strlen("env: "));
		write(2, cmds->args[0], ft_strlen(cmds->args[0]));
		write(2, ": No such file or directory\n", \
		ft_strlen(": No such file or directory\n"));
		return ;
	}
	else if (cmds->cmd && ft_strncmp2(cmds->cmd, "echo") == 0)
		ft_echo(cmds);
	else if (cmds->cmd && ft_strncmp2(cmds->cmd, "pwd") == 0)
		pwd(cmds);
}

void	check_built(t_cmds *cmds)
{
	if (cmds->cmd && check_cmmn(cmds->cmd, "exit") == 0)
		exitmini(cmds);
	else if (cmds->cmd && check_cmmn(cmds->cmd, "export") == 0
		&& cmds->args[0])
		new_envr(cmds, -1, -1, 0);
	else if (cmds->cmd && check_cmmn(cmds->cmd, "export") == 0
		&& !cmds->args[0])
		print_env(cmds, 1);
	else if (cmds->cmd && check_cmmn(cmds->cmd, "unset") == 0
		&& (cmds->status == NONE || cmds->status == BUILTIN))
		unset_env(cmds);
	else if (cmds->cmd && check_cmmn(cmds->cmd, "cd") == 0)
		cd(cmds, cmds->args[0]);
	check_built_2(cmds);
}

void	check_built_f(t_cmds *cmds)
{
	if (cmds->cmd && check_cmmn(cmds->cmd, "exit") == 0)
		cmds->status = BUILTIN;
	else if (cmds->cmd && check_cmmn(cmds->cmd, "export") == 0
		&& cmds->args[0])
		cmds->status = BUILTIN;
	else if (cmds->cmd && check_cmmn(cmds->cmd, "export") == 0
		&& !cmds->args[0])
		cmds->status = BUILTIN;
	else if (cmds->cmd && check_cmmn(cmds->cmd, "unset") == 0)
		cmds->status = BUILTIN;
	else if (cmds->cmd && check_cmmn(cmds->cmd, "cd") == 0)
		cmds->status = BUILTIN;
	else if (cmds->cmd && ft_strncmp2(cmds->cmd, "env") == 0
		&& !cmds->args[0])
		cmds->status = BUILTIN;
	else if (cmds->cmd && ft_strncmp2(cmds->cmd, "env") == 0
		&& cmds->args[0])
		cmds->status = BUILTIN;
	else if (cmds->cmd && ft_strncmp2(cmds->cmd, "echo") == 0)
		cmds->status = BUILTIN;
	else if (cmds->cmd && ft_strncmp2(cmds->cmd, "pwd") == 0)
		cmds->status = BUILTIN;
}
