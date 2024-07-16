/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:39:17 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_in_env(t_cmds *cmds, char *name)
{
	char	*temp;
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	if (ft_strnstr(name, "0", ft_strlen(name)))
		return (ft_strdup(cmds->env->minipwd));
	if (ft_strnstr(name, "?", ft_strlen(name)))
		return (ft_itoa(g_globals_exit));
	while (cmds->env->envr[i])
	{
		temp = ft_substr(cmds->env->envr[i], 0, ft_strlen(cmds->env->envr[i])
				- ft_strlen(&cmds->env->envr[i][search_eq(cmds->env->envr[i])] \
				));
		if (ft_strncmp(name, temp, ft_strlen(name)) == 0
			&& ft_strncmp(name, temp, ft_strlen(temp)) == 0)
		{
			value = ft_strdup(ft_strchr(cmds->env->envr[i], '=') + 1);
			return (free (temp), value);
		}
		free(temp);
		i++;
	}
	return (value);
}

void	del_from_str(char	**str, int start, int end)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp1 = ft_substr(*str, 0, start);
	temp2 = ft_substr(*str, end, ft_strlen((*str) + end));
	temp = ft_strjoin(temp1, temp2);
	free(*str);
	free(temp1);
	free(temp2);
	*str = temp;
}

void	replace_in_str_utils(int start, int i, char **str, char *value)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	temp = ft_substr(*str, 0, start);
	temp2 = replace_check_dol(value);
	if (temp[0] && temp2 != NULL)
	{
		temp1 = ft_strjoin(temp, temp2);
		free(temp2);
	}
	else if (temp2)
		temp1 = temp2;
	else
		temp1 = ft_strjoin(temp, value);
	free(temp);
	free(value);
	temp = ft_strjoin(temp1, (*str) + i);
	free(*str);
	free(temp1);
	*str = temp;
}

void	replace_in_str(t_cmds	*cmds, char	**str, int start)
{
	char	*name;
	char	*value;
	int		i;

	i = start + 1;
	if ((*str)[i] == '?' || (*str)[i] == '0')
		i++;
	else
		while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '$'
			&& (*str)[i] != '\'' && (*str)[i] != '"' && (ft_isalnum((*str)[i])
				|| (*str)[i] == '_') && !((*str)[i] == '0' && i != 0
					&& (*str)[i - 1] == '$'))
			i++;
	name = ft_substr(*str, start + 1, i - start - 1);
	value = search_in_env(cmds, name);
	if (ft_strnstr(*str + (i - 2), "\"$\"", 3))
		value = ft_strdup("$");
	if (value == NULL)
		del_from_str(str, start, i);
	else
		return (replace_in_str_utils(start, i, str, value), free(name));
	free(name);
}

void	check_dollar(t_cmds	*cmds, char	**str, int single_quote, int dble_quote)
{
	int	i;

	i = 0;
	while ((*str) && (*str)[i])
	{
		quote_check((*str)[i], &single_quote, &dble_quote);
		if ((*str)[i] == '$' && (*str)[i + 1] && ((*str)[i + 1] == '\''
			|| (*str)[i + 1] == '"') && single_quote % 2 == 0
				&& dble_quote % 2 == 0)
		{
			del_from_str(str, i, i + 1);
			for_zero(&i, &single_quote, &dble_quote);
			continue ;
		}
		else if (else_control(str, i, single_quote) == EXIT_SUCCESS)
		{
			replace_in_str(cmds, str, i);
			for_zero(&i, &single_quote, &dble_quote);
			continue ;
		}
		i++;
		if (!(*str)[0])
			break ;
	}
}
