/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:41:08 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	take_output(char *str, t_cmds *cmds, int j, int type)
{
	char	*temp;
	int		start;

	cmds->utils.i += 1;
	cmds->utils.single_quote = 0;
	cmds->utils.dble_quote = 0;
	while (str[cmds->utils.i] && str[cmds->utils.i] == ' ')
		cmds->utils.i++;
	if (!str[cmds->utils.i])
		return (assign_var(cmds, NULL, j, type), cmds->utils.i);
	start = cmds->utils.i;
	while (str[cmds->utils.i])
	{
		quote_check(str[cmds->utils.i], &cmds->utils.single_quote,
			&cmds->utils.dble_quote);
		if ((str[cmds->utils.i] == '>' || str[cmds->utils.i] == '<'
				|| str[cmds->utils.i] == ' ') && cmds->utils.dble_quote % 2 == 0
			&& cmds->utils.single_quote % 2 == 0)
			break ;
		cmds->utils.i++;
	}
	temp = ft_substr(str, start, cmds->utils.i - start);
	del_ind(&temp);
	return (assign_var(cmds, temp, j, type), cmds->utils.i);
}

int	continue_to_loop(t_cmds	*cmds, char *str)
{
	quote_check(str[cmds->utils.i], &cmds->utils.single_quote,
		&cmds->utils.dble_quote);
	if (str[cmds->utils.i] == '>' && cmds->utils.single_quote % 2 == 0
		&& cmds->utils.dble_quote % 2 == 0)
	{
		if (str[cmds->utils.i + 1] && str[cmds->utils.i + 1] == '>')
		{
			if (take_append(cmds, str) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
			if (go_take_output(cmds, str) == EXIT_FAILURE)
				return (EXIT_FAILURE);
	}
	else if (str[cmds->utils.i] == '<' && cmds->utils.single_quote % 2 == 0
		&& cmds->utils.dble_quote % 2 == 0)
	{
		if (check_input(cmds, str) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		cmds->utils.i++;
	return (EXIT_SUCCESS);
}

void	take_output_first(char *str, t_cmds *cmds)
{
	init_take_output(cmds, str);
	while (str[cmds->utils.i])
		if (continue_to_loop(cmds, str) == EXIT_FAILURE)
			break ;
	cmds->output[cmds->utils.j] = NULL;
	cmds->append[cmds->utils.k] = NULL;
}

void	take_(char **args, t_cmds *cmds, t_main_env *env)
{
	t_cmds	*temp;
	int		i;

	i = 0;
	temp = cmds;
	while (args[i])
	{
		take_all(args[i], cmds);
		if (args[i + 1])
		{
			cmds->status = status_control(cmds->status, PIPE);
			cmds->next = malloc(sizeof(t_cmds));
			cmds = cmds->next;
			cmds->env = env;
			init_env(env, cmds);
			take_env(cmds, env, 1, NULL);
		}
		i++;
	}
	freecpointer(args);
	cmds->next = NULL;
	cmds = temp;
}

void	parse_args(char **args, t_cmds *cmds, t_main_env *env)
{
	take_(args, cmds, env);
	cmd_start(cmds);
}
