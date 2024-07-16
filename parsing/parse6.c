/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:40:35 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_strdup2(char *str)
{
	char	*ret;

	ret = ft_strdup(str);
	free(str);
	return (ret);
}

int	skip_arg(char *str, int *single_quote, int *dble_quote, int i)
{
	if (str[i] && (str[i] == '\'' || str[i] == '"'))
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && !((str[i] == ' ' || str[i] == '>' || str[i] == '<')
			&& *single_quote % 2 == 0 && *dble_quote % 2 == 0))
	{
		quote_check(str[i], single_quote, dble_quote);
		i++;
	}
	return (i);
}

static int	take_args_adv(char **str, int single_quote, int dble_quote, int i)
{
	i = skip_input_output(*str, single_quote, dble_quote, i);
	if ((*str)[0] == '>' || (*str)[0] == '<')
		if ((*str)[i])
			i = skip_cmd(*str, i, single_quote, dble_quote);
	return (i);
}

static int	take_args_adv_2(t_cmds	*cmds, char	*str,
	int single_quote, int dble_quote)
{
	int	i;

	i = take_flags(str, cmds, single_quote, dble_quote);
	cmds->args = malloc(sizeof(char *) * (args_count(str, 0, 0, i) + 1));
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

void	take_args_and_flags(t_cmds	*cmds, char	*str,
	int single_quote, int dble_quote)
{
	char	*temp;
	int		start;
	int		j;
	int		i;

	i = take_args_adv_2(cmds, str, single_quote, dble_quote);
	j = 0;
	while (str[i])
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] && (str[i] == '>' || str[i] == '<') && single_quote % 2 == 0
			&& dble_quote % 2 == 0)
			i = take_args_adv(&str, single_quote, dble_quote, i);
		else if (str[i] && str[i] != ' ')
		{
			start = i;
			i = skip_arg(str, &single_quote, &dble_quote, i);
			temp = ft_substr_trim(str, start, i - start, " \t");
			del_ind(&temp);
			cmds->args[j++] = ft_strdup2(temp);
		}
		else
			i++;
	}
	cmds->args[j] = NULL;
}
