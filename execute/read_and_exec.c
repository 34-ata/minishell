/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:59 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 18:58:24 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	non_child_builtin(t_cmds *temp, int i)
{
	if ((temp->output[0] || temp->status == APPEND) && i == 1)
	{
		if (set_fork_and_output_2(temp, i) == -1)
		{
			g_globals_exit = 1;
			return ;
		}
	}
	check_built_f(temp);
	if (temp->input[0] && i == 1 && temp->status == BUILTIN)
	{
		if (set_input(temp, i) == -1)
		{
			g_globals_exit = 1;
			return ;
		}
	}
	if (temp->status == BUILTIN && i == 1)
		check_built(temp);
}

static void	non_pipe(char **run, t_cmds *temp, int i)
{
	temp->pid = fork();
	if (temp->pid == 0)
	{
		set_signal(CHILD_P);
		childproces(run, temp, i);
		exit(g_globals_exit);
	}
	non_child_builtin(temp, i);
}

static char	**commandstr2(t_cmds *temp, int i, int n, int b)
{
	char	**run;

	run = malloc(sizeof(char *) * (commandcounter(temp) + 2));
	if (!run)
		return (NULL);
	if (!temp->cmd)
		run[n++] = NULL;
	else
		run[n++] = ft_strdup(temp->cmd);
	while (temp->flags[i])
		run[n++] = ft_strdup(temp->flags[i++]);
	b = 0;
	while (temp->args[b])
		run[n++] = ft_strdup(temp->args[b++]);
	run[n] = NULL;
	return (run);
}

static void	pipe_exec(char **run, t_cmds *temp, int i)
{
	int		p[2];

	pipecheck(p);
	temp->pid = fork();
	if (temp->pid == 0)
	{
		set_signal(CHILD_P);
		close(p[0]);
		set_input(temp, i);
		set_output(temp, p, i);
		close(p[1]);
		check_built_f(temp);
		builtornot(temp, run);
	}
	close(p[1]);
	dup2(p[0], 0);
	close(p[0]);
}

void	read_and_exec(t_cmds *cmds, int i)
{
	t_cmds	*temp;
	char	**run;
	int		fd[2];

	temp = cmds;
	backup_default_fd(fd);
	while (temp)
	{
		run = commandstr2(temp, 0, 0, 0);
		if (status_check(temp) == 1)
			pipe_exec(run, temp, i);
		else if (status_check(temp) == 2)
		{
			pipe_heredoc(temp, run, fd);
			if (g_globals_exit == 130)
				break ;
			pipe_exec(run, temp, i);
		}
		else if (status_check(temp) == 3)
			non_pipe(run, temp, i);
		freecpointer(run);
		temp = temp->next;
	}
	closedup(fd);
	get_exit_status(cmds, i);
}
