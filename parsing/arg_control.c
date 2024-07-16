/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:58:49 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	empty_input_output(char *str, int single_quote, int dble_quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if ((str[i] == '<' || str[i] == '>') && single_quote % 2 == 0
			&& dble_quote % 2 == 0)
		{
			if ((str[i] == '<' && str[i + 1] == '<')
				|| (str[i] == '>' && str[i + 1] == '>'))
				i += 1;
			if (str[i] == '<' || str[i] == '>')
				i += 1;
			while (str[i] && str[i] == ' ')
				i++;
			if (!str[i] || str[i] == '<' || str[i] == '>'
				|| str[i] == '|' || str[i] == '#')
				return (i);
		}
		else
			i++;
	}
	return (-1);
}

int	empty_pipe_check(char	*str, int single_quote, int dble_quote)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] != '<' && str[i] != '>' && str[i] != '"' && str[i] != '\''
			&& str[i] != '|')
			count++;
		if (str[i] == '|' && single_quote % 2 == 0 && dble_quote % 2 == 0)
		{
			while (str[++i] && str[i] == ' ')
				;
			if (!str[i])
				return (0);
			if (str[i] == '|' || count == 0)
				return (-1);
		}
		else
			i++;
	}
	return (1);
}

int	dquote_check(char *str, int single_quote, int dble_quote)
{
	int	i;

	i = 0;
	while (str[i])
		quote_check(str[i++], &single_quote, &dble_quote);
	if (single_quote % 2 != 0 || dble_quote % 2 != 0)
		return (0);
	return (1);
}

int	arg_control(char *str)
{
	if (empty_pipe_check(str, 0, 0) == -1 || empty_pipe_check(str, 0, 0) == 0)
	{
		ft_putstr_fd("minishell: syntax error  near unexpected token `|'\n", 2);
		g_globals_exit = 258;
		return (0);
	}
	else if (!dquote_check(str, 0, 0))
	{
		g_globals_exit = 258;
		return (ft_putstr_fd("dquote!\n", 2), 0);
	}
	else if (empty_input_output(str, 0, 0) != -1)
	{
		ft_putstr_fd("minishell: syntax error ", 2);
		if (str[empty_input_output(str, 0, 0)] == '\0')
			ft_putstr_fd("near unexpected token `newline'\n", 2);
		else
			token_error(str);
		g_globals_exit = 258;
		return (0);
	}
	return (1);
}
