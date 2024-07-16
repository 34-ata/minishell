/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/10 19:25:41 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	output_count(char *str, int single_quote, int dble_quote, int type)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] == '>' && single_quote % 2 == 0 && dble_quote % 2 == 0)
		{
			if (str[i + 1] && str[i + 1] != '>' && type != APPEND)
				count += 1;
			else if (str[i + 1] && str[i + 1] == '>' && type == APPEND)
				count += 1;
			else if (str[i + 1] && str[i + 1] == '>' && type != APPEND)
				i++;
		}
		i++;
	}
	return (count);
}

int	input_count(char *str, int single_quote, int dble_quote, int type)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] == '<' && single_quote % 2 == 0 && dble_quote % 2 == 0)
		{
			if (str[i + 1] && str[i + 1] != '<' && type != HEREDOC)
				count += 1;
			else if (str[i + 1] && str[i + 1] == '<' && type == HEREDOC)
				count += 1;
			else if (str[i + 1] && str[i + 1] == '<' && type != HEREDOC)
				i++;
		}
		i++;
	}
	return (count);
}

static int	flags_count_if(char *str, int single_quote, int dble_quote, int i)
{
	if (str[i] && !((str[i] == '>' || str[i] == '<')
			&& single_quote % 2 == 0 && dble_quote % 2 == 0))
		return (1);
	return (0);
}

int	flags_count(char *str, int i, int single_quote, int dble_quote)
{
	char	*temp;
	int		count;
	int		start;

	count = 0;
	start = i;
	while (flags_count_if(str, single_quote, dble_quote, i) == 1)
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] == '-')
		{
			i = find_valid_space(str, i, single_quote, dble_quote);
			temp = ft_substr_trim(str, start, i - start, " ");
			del_ind(&temp);
			if (temp[0] && temp[0] == '-' && temp[1] != '\0')
				count += 1;
			else
				return (free(temp), count);
			free (temp);
			start = i;
		}
		else
			i++;
	}
	return (count);
}

int	args_count(char *str, int single_quote, int dble_quote, int i)
{
	int	count;

	count = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] && (str[i] == '>' || str[i] == '<') && single_quote % 2 == 0
			&& dble_quote % 2 == 0)
			i = skip_input_output(str, single_quote, dble_quote, i);
		else if (str[i])
		{
			count += 1;
			i = skip_arg(str, &single_quote, &dble_quote, i);
		}
		else
			i++;
	}
	return (count);
}
