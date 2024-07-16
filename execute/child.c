/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:49 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/06 15:30:16 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtornot(t_cmds *temp, char **run)
{
	if (temp->status != BUILTIN)
		runcommand(run, temp);
	else
		check_built(temp);
	exit(127);
}

void	childproces(char **run, t_cmds *temp, int i)
{
	if (i == 1)
		check_built_f(temp);
	if ((temp->output[0] || (temp->status == APPEND))
		&& (i != 1 || temp->status != BUILTIN))
		set_fork_and_output(temp, i);
	if (i != 1)
		check_built_f(temp);
	if (temp->input[0] && (i != 1 || temp->status != BUILTIN))
		set_input(temp, i);
	if (temp->status != BUILTIN)
		runcommand(run, temp);
	if (temp->status == BUILTIN && i != 1)
	{
		check_built(temp);
		exit(0);
	}
}
