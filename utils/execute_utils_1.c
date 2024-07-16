/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:53:19 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:12:56 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_input(t_cmds *temp, int c)
{
	int	fd;
	int	i;

	i = 0;
	if (!temp->input || !temp->input[0])
		return (-1);
	while (temp->input[i])
	{
		fd = open(temp->input[i], O_RDONLY, 0644);
		if (fd == -1 && (c != 1 || temp->status != BUILTIN))
			fderror(temp->input[i]);
		else if (c == 1 && fd == -1)
		{
			fderror2(temp->input[i]);
			return (fd);
		}
		if (temp->input[i + 1])
			close(fd);
		i++;
	}
	dup2(fd, 0);
	close(fd);
	return (fd);
}

int	open_output(t_cmds *temp, int c)
{
	int	i;
	int	fd;

	i = 0;
	if (!temp->output)
		return (1);
	while (temp->output[i])
	{
		fd = open(temp->output[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1 && (c != 1 || temp->status != BUILTIN))
			fderror(temp->output[i]);
		else if (c == 1 && fd == -1)
		{
			fderror2(temp->output[i]);
			return (-1);
		}
		if (temp->output[i + 1])
			close(fd);
		i++;
	}
	return (fd);
}

int	open_output_append(t_cmds *temp, int c)
{
	int	i;
	int	fd;

	i = 0;
	if (!temp->append)
		return (1);
	while (temp->append[i])
	{
		fd = open(temp->append[i], O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1 && (c != 1 || temp->status != BUILTIN))
			fderror(temp->append[i]);
		else if (c == 1 && fd == -1)
		{
			fderror2(temp->append[i]);
			return (-1);
		}
		if (temp->append[i + 1])
			close(fd);
		i++;
	}
	return (fd);
}

static int	outputandappendcheck(t_cmds *temp)
{
	if (temp->next != NULL && temp->output[0] == NULL
		&& temp->append[0] == NULL)
		return (1);
	else if ((temp->output[0] != NULL || temp->append[0] != NULL))
		return (2);
	return (0);
}

int	set_output(t_cmds *temp, int p[2], int i)
{
	int	fd;

	close(p[0]);
	if (outputandappendcheck(temp) == 1)
		dup2(p[1], 1);
	else if (outputandappendcheck(temp) == 2)
	{
		if ((temp->status == PIPEAPPEND || temp->status == PIPEHEREDOCAPPEND)
			|| temp->status == HEREDOCAPPEND)
		{
			fd = open_output_append(temp, i);
			open_output(temp, i);
		}
		else
		{
			fd = open_output(temp, i);
			open_output_append(temp, i);
		}
		dup2(fd, 1);
		close(fd);
		return (fd);
	}
	return (0);
}
