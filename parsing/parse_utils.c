/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:56:29 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	take_all(char *str, t_cmds *cmds)
{
	take_output_first(str, cmds);
	take_input_first(str, cmds);
	take_cmd(str, cmds, 0, 0);
	take_args_and_flags(cmds, str, 0, 0);
}

void	cmd_start(t_cmds *cmds)
{
	int	i;
	int	fd;

	i = 0;
	if (!cmds->cmd && !cmds->next && (cmds->input[0]))
	{
		while (cmds->input[i])
		{
			fd = open(cmds->input[i], O_RDONLY, 0644);
			if (fd == -1)
				fderror2(cmds->input[i]);
			close(fd);
			i++;
		}
	}
	if (!cmds->cmd && !cmds->next && cmds->status == HEREDOC)
		nocmd_heredoc(cmds, 0, 0, NULL);
	if (!cmds->cmd && !cmds->next)
	{
		g_globals_exit = 0;
		return ;
	}
	read_and_exec(cmds, commanlistcount(cmds));
}

void	init_env(t_main_env	*env, t_cmds	*cmds)
{
	if (!cmds->env)
		cmds->env = env;
	cmds->status = NONE;
	cmds->append = NULL;
	cmds->args = NULL;
	cmds->cmd = NULL;
	cmds->flags = NULL;
	cmds->heredoc = NULL;
	cmds->input = NULL;
	cmds->output = NULL;
}

int	check_flags_2(int i, t_cmds *cmds)
{
	int	j;

	j = 1;
	if (i < 0)
		return (-1);
	while (cmds->flags[i] && cmds->flags[i][j])
	{
		if (cmds->flags[i][j] && cmds->flags[i][j] != 'n')
			return (i);
		j++;
	}
	return (-1);
}

void	for_zero(int *i, int *single_quote, int *dble_quote)
{
	*single_quote = 0;
	*dble_quote = 0;
	*i = 0;
}
