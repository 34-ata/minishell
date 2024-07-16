/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:52 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:37:06 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exit_ut(int i, int n, t_cmds *cmd)
{
	if (i + n > 1)
	{
		if (i > 0)
			if (!ft_isnumeric(cmd->args[0]))
				exit_error(cmd);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_globals_exit = 1;
		return (1);
	}
	else if (i + n == 1 && n == 0)
	{
		if (!ft_isnumeric(cmd->args[0]))
			exit_error(cmd);
		if (cmd->args[0])
			exit(ft_atoi(cmd->args[0]));
	}
	if (i + n == 1 && i == 0)
	{
		if (cmd->flags[0] && cmd->flags[0][0] == '-' && cmd->flags[0][1] == '-')
			exit_error_2(cmd);
		if (cmd->flags[0] && cmd->flags[0][0] == '-')
			exit(ft_atoi(cmd->flags[0]));
	}
	return (0);
}

void	exit_error(t_cmds *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	g_globals_exit = 255;
	exit (255);
}

int	exitarg(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i] && cmd->args)
		i++;
	return (i);
}

int	exitflag(t_cmds *cmd)
{
	int	i;

	i = 0;
	while (cmd->flags[i] && cmd->flags)
		i++;
	return (i);
}

int	is_valid(char *arg, int control)
{
	int	i;

	i = -1;
	if ((ft_isdigit(arg[0]) || !ft_isalpha(arg[0])) && arg[0] != '_')
	{
		if (control == 1)
			return (ft_msg(arg, ERR_NOT_VALID), 1);
		return (1);
	}
	while (arg[++i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			if (control == 1)
				return (ft_msg(arg, ERR_NOT_VALID), 1);
			return (1);
		}
	}
	if (arg[i] == '=')
		return (0);
	else
		return (1);
}
