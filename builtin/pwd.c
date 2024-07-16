/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:43:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/09 14:44:45 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(t_cmds *cmd)
{
	char	*s;

	if (cmd->next == NULL)
		cmd->status = BUILTIN;
	s = getcwd(NULL, 0);
	printf("%s\n", s);
	g_globals_exit = 0;
	free(s);
}
