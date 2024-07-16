/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking_output_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 18:08:33 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	take_output2(int i, int fd, t_cmds *cmds)
{
	char	*temp;

	i = 0;
	while (cmds->output && cmds->output[i])
		i++;
	if (i == 0)
		return (1);
	temp = cmds->output[i - 1];
	fd = open(temp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	take_outpu3_adv(int fd, char *temp, t_cmds *cmds)
{
	fd = open(temp, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		cmds->status = status_control(cmds->status, APPEND);
		return (0);
	}
	close(fd);
	return (1);
}

int	take_output3(int i, int fd, t_cmds *cmds)
{
	char	*temp;

	i = 0;
	while (cmds->append[i])
		i++;
	temp = cmds->append[i - 1];
	return (take_outpu3_adv(fd, temp, cmds));
}
