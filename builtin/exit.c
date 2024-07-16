/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:43:21 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/15 13:43:10 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	stat_check2(t_cmds *cmd)
{
	t_cmds	*temp;

	temp = cmd;
	while (temp)
	{
		if (status_check(temp) == 2)
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	get_exit_status(t_cmds *cmds, int i)
{
	pid_t	j;
	int		status;
	t_cmds	*mini;

	status = 0;
	mini = cmds;
	if (g_globals_exit == 130 && stat_check2(cmds) == 1)
	{
		g_globals_exit = 1;
		return ;
	}
	while (mini)
	{
		signal(SIGINT, &handler_sigint);
		j = waitpid(mini->pid, &status, 0);
		if (j < 0)
			continue ;
		if (i == 1 && mini->status == BUILTIN)
			break ;
		if (WIFEXITED(status))
			g_globals_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_globals_exit = 128 + WTERMSIG(status);
		mini = mini->next;
	}
}

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	cleanenv(t_cmds *cmd)
{
	freecpointer(cmd->env->envr);
	free(cmd->env->minipwd);
	free(cmd->env);
}

void	exitmini(t_cmds *cmd)
{
	int	i;
	int	n;

	n = exitflag(cmd);
	i = exitarg(cmd);
	if (cmd->pid == 0)
		return ;
	printf("exit\n");
	if (cmd->cmd && ft_strncmp2(cmd->cmd, "exit") == 0)
		if (exit_ut (i, n, cmd) == 1)
			return ;
	cleanlist(cmd);
	cleanenv(cmd);
	exit (g_globals_exit);
}
