/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking_output_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 18:08:39 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_take_output(t_cmds	*cmds, char *str)
{
	cmds->utils.i = 0;
	cmds->utils.dble_quote = 0;
	cmds->utils.single_quote = 0;
	cmds->utils.j = 0;
	cmds->utils.k = 0;
	cmds->output = malloc(sizeof(char *) * (output_count(str, 0, 0, 0) + 1));
	if (!cmds->output)
		perror("Malloc!\n");
	cmds->append = malloc(sizeof(char *)
			* (output_count(str, 0, 0, APPEND) + 1));
	if (!cmds->append)
		perror("Malloc!\n");
}

void	assign_var(t_cmds *cmds, char *temp, int j, int type)
{
	if (type != APPEND)
	{
		cmds->output[j] = temp;
		cmds->output[j + 1] = NULL;
	}
	else
	{
		cmds->append[j] = temp;
		cmds->append[j + 1] = NULL;
	}
}

int	check_input(t_cmds	*cmds, char *str)
{
	if (take_input2(str, cmds->utils.i) == 0)
		return (EXIT_FAILURE);
	cmds->utils.i++;
	return (EXIT_SUCCESS);
}

int	go_take_output(t_cmds *cmds, char *str)
{
	cmds->utils.c = cmds->utils.i;
	cmds->utils.i = take_output(str, cmds, cmds->utils.j++, 0);
	if (take_output2(cmds->utils.c, 0, cmds) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	take_append(t_cmds *cmds, char *str)
{
	cmds->utils.c = cmds->utils.i++;
	cmds->utils.i = take_output(str, cmds, cmds->utils.k, APPEND);
	if (cmds->utils.j + cmds->utils.k == output_count(str, 0, 0, 0)
		+ output_count(str, 0, 0, APPEND) - 1)
		cmds->status = status_control(cmds->status, APPEND);
	cmds->utils.k++;
	if (take_output3(cmds->utils.c + 1, 0, cmds) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
