/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:56 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 18:58:35 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	backup_default_fd(int fd[2])
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

static void	exitheredoc(void)
{
	g_globals_exit = 130;
	exit(130);
}

void	nocmd_heredoc(t_cmds *temp, int i, int c, char *lll)
{
	i = 0;
	c = fork();
	if (c == 0)
	{
		set_signal(HEREDOC_P);
		while (temp->heredoc[i])
		{
			if (g_globals_exit == 999)
			{
				free(lll);
				break ;
			}
			lll = readline("> ");
			if (!lll)
				break ;
			if (g_globals_exit == 999)
				continue ;
			if (check_cmmn(temp->heredoc[i], lll) == 0)
				i++;
			free(lll);
		}
		exit(0);
	}
	waitpid(c, 0, 0);
}

static void	pheredoc(int fd[2], t_cmds *temp, int p[2])
{
	int		i;
	char	*lll;

	i = 0;
	dup2(fd[0], 0);
	while (temp->heredoc[i])
	{
		if (g_globals_exit == 999)
		{
			free(lll);
			exit(130);
		}
		lll = readline("> ");
		if (!lll)
			exitheredoc();
		if (g_globals_exit == 999)
			continue ;
		if (lll && temp->heredoc[i + 1] == NULL
			&& check_cmmn(temp->heredoc[i], lll) != 0)
			ft_putendl_fd(lll, p[1]);
		if (check_cmmn(temp->heredoc[i], lll) == 0)
			i++;
		free(lll);
	}
	exit(0);
}

void	pipe_heredoc(t_cmds *temp, char **run, int fd[2])
{
	int		p[2];
	int		status;

	pipecheck(p);
	temp->pid = fork();
	if (temp->pid == 0)
	{
		set_signal(HEREDOC_P);
		pheredoc(fd, temp, p);
	}
	close(p[1]);
	dup2(p[0], 0);
	close(p[0]);
	waitpid(temp->pid, &status, 0);
	if (WIFEXITED(status))
		g_globals_exit = WEXITSTATUS(status);
	if (g_globals_exit == 130)
		freecpointer(run);
}
