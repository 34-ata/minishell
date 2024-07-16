/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:53:39 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:12:54 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_fork_and_output(t_cmds *temp, int i)
{
	int	fd;

	if (temp->status == APPEND)
	{
		fd = open_output_append(temp, i);
		if (fd == -1)
			return (fd);
		open_output(temp, i);
	}
	else
	{
		fd = open_output(temp, i);
		if (fd == -1)
			return (fd);
		open_output_append(temp, i);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	set_fork_and_output_2(t_cmds *temp, int i)
{
	int	fd;
	int	t;

	t = temp->status;
	check_built_f(temp);
	if (temp->status != BUILTIN)
		return (0);
	if ((t == APPEND) && temp->status == BUILTIN)
	{
		fd = open_output_append(temp, i);
		if (fd == -1)
			return (fd);
		open_output(temp, i);
	}
	else
	{
		fd = open_output(temp, i);
		if (fd == -1)
			return (fd);
		open_output_append(temp, i);
	}
	dup2(fd, 1);
	close(fd);
	return (fd);
}

int	commandcounter(t_cmds *temp)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	while (temp->flags[i])
		i++;
	while (temp->args[c])
		c++;
	return (i + c);
}

int	commanlistcount(t_cmds *cmd)
{
	int		i;
	t_cmds	*temp;

	i = 0;
	temp = cmd;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	status_check(t_cmds *temp)
{
	if (temp->status == PIPE || temp->status == PIPEAPPEND)
		return (1);
	else if (temp->status == HEREDOC || temp->status == HEREDOCAPPEND
		|| temp->status == PIPEHEREDOC || temp->status == PIPEHEREDOCAPPEND)
		return (2);
	else
		return (3);
}
