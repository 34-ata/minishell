/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:13:21 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	quote_check(char c, int *single_quote, int *dble_quote)
{
	if (c == '\'' && *dble_quote % 2 == 0)
		*single_quote += 1;
	else if (c == '"' && *single_quote % 2 == 0)
		*dble_quote += 1;
}

int	find_valid_space(char *str, int i, int single_quote, int dble_quote)
{
	while (str[i])
	{
		if (str[i] == '\'' && dble_quote % 2 == 0)
			single_quote += 1;
		else if (str[i] == '"' && single_quote % 2 == 0)
			dble_quote += 1;
		if (str[i] == ' ' && single_quote % 2 == 0 && dble_quote % 2 == 0)
			break ;
		i++;
	}
	return (i);
}

static int	take_flags_adv(char *str, t_cmds *cmds, int *start, int *j)
{
	int	i;

	i = skip_cmd(str, 0, 0, 0);
	cmds->flags = malloc(sizeof(char *) * (flags_count(str, i, 0, 0) + 1));
	cmds->flags[flags_count(str, i, 0, 0)] = NULL;
	*start = i;
	*j = 0;
	return (i);
}

int	take_flags(char *str, t_cmds *cmds, int single_quote, int dble_quote)
{
	char	*temp;
	int		start;
	int		i;
	int		j;

	i = take_flags_adv(str, cmds, &start, &j);
	while (str[i] && !((str[i] == '>' || str[i] == '<')
			&& single_quote % 2 == 0 && dble_quote % 2 == 0))
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] == '-')
		{
			i = find_valid_space(str, i, single_quote, dble_quote);
			temp = ft_substr_trim(str, start, i - start, " ");
			del_ind(&temp);
			if (temp[0] && temp[0] == '-' && temp[1] != '\0')
				cmds->flags[j++] = temp;
			else
				return (free(temp), start);
			start = i;
		}
		else
			i++;
	}
	return (start);
}
