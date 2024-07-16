/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/15 12:37:27 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	freecpointer(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_double_pointers(t_cmds *cmd)
{
	freecpointer(cmd->args);
	freecpointer(cmd->flags);
	freecpointer(cmd->output);
	freecpointer(cmd->input);
	freecpointer(cmd->append);
	freecpointer(cmd->heredoc);
	freecpointer(cmd->envr);
}

void	cleanlist(t_cmds	*cmd)
{
	t_cmds	*temp;
	int		i;

	i = 0;
	temp = cmd;
	while (cmd)
	{
		if (cmd->cmd)
			free(cmd->cmd);
		free_double_pointers(cmd);
		cmd = cmd->next;
	}
	while (temp)
	{
		cmd = temp;
		temp = temp->next;
		if (i == 1)
			free(cmd);
		i = 1;
	}
}

char	*ft_substr_trim(char *str, int start, int end, char *spt)
{
	char	*temp;
	char	*ret;

	temp = ft_substr(str, start, end);
	ret = ft_strtrim(temp, spt);
	free(temp);
	return (ret);
}

int	else_control(char	**str, int i, int single_quote)
{
	if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != ' '
			&& (*str)[i + 1] != '\'' && (*str)[i + 1] != '"'
			&& single_quote % 2 == 0 && (*str)[i + 1] != '.')
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
