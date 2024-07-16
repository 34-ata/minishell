/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:43:27 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:27:45 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	specval(char *str)
{
	if (str[0] != '0' || str[0] != '?')
		return (0);
	if (str[0] == '?')
		printf("%i", g_globals_exit);
	if (str[0] == '0')
		printf("./minishell");
	printf("%s", str + 1);
	return (1);
}

char	*find_inpath(t_cmds *cmds, char *str)
{
	int	i;

	i = -1;
	if (specval(str) == 1)
		return (0);
	while (cmds->envr[++i])
		if (ft_strncmp(cmds->envr[i], str, search_eq(cmds->envr[i])) == 0
			&& ft_strncmp(cmds->envr[i], str, ft_strlen(str)) == 0)
			return (ft_strchr(cmds->envr[i], '=') + 1);
	return (0);
}

void	print_(t_cmds *cmds)
{
	int	i;

	i = -1;
	g_globals_exit = 0;
	while (cmds->args[++i])
	{
		printf("%s", cmds->args[i]);
		if (cmds->args[i + 1])
			printf(" ");
	}
}

int	check_flags(t_cmds	*cmds)
{
	int	j;
	int	i;

	i = 0;
	while (cmds->flags[i])
	{
		j = 1;
		while (cmds->flags[i][j])
		{
			if (cmds->flags[i][j] && cmds->flags[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

void	ft_echo(t_cmds *cmds)
{
	int	status;
	int	i;

	i = check_flags(cmds);
	status = i;
	if (i != -1)
	{
		while (cmds->flags[i])
		{
			printf("%s", cmds->flags[i]);
			if (cmds->flags[i + 1])
				printf(" ");
			i++;
		}
		printf(" ");
	}
	if (cmds->args[0])
		print_(cmds);
	if ((status != -1 && !(status > 0)) || !cmds->flags[0])
		printf("\n");
}
