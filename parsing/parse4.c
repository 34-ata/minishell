/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:13:22 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	skip_input_output(char	*str, int single_quote, int dble_quote, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<'))
		i++;
	while (str[i] && !(str[i] == ' ' && single_quote % 2 == 0
			&& dble_quote % 2 == 0))
	{
		quote_check(str[i], &single_quote, &dble_quote);
		i++;
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '>' || str[i] == '<'))
		i = skip_input_output(str, 0, 0, i);
	return (i);
}

void	take_cmd(char	*str, t_cmds *cmds, int single_quote, int dble_quote)
{
	char	*cmd;
	int		start;
	int		i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '>' || str[i] == '<'))
		i = skip_input_output(str, 0, 0, 0);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i])
		start = i;
	else
		return ;
	while (str[i] && !((str[i] == ' ' || str[i] == '>' || str[i] == '<')
			&& single_quote % 2 == 0 && dble_quote % 2 == 0))
	{
		quote_check(str[i], &single_quote, &dble_quote);
		i++;
	}
	cmd = ft_substr(str, start, i - start);
	del_ind(&cmd);
	cmds->cmd = cmd;
}

int	skip_cmd(char *str, int i, int single_quote, int dble_quote)
{
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && !((str[i] == ' ' || str[i] == '>' || str[i] == '<')
			&& single_quote % 2 == 0 && dble_quote % 2 == 0))
	{
		quote_check(str[i], &single_quote, &dble_quote);
		i++;
	}
	return (i);
}
