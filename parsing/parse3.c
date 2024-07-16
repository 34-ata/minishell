/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:26:06 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:41:27 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	take_input_adv(char *str, t_cmds *cmds, char **temp)
{
	int	start;

	start = cmds->utils.i;
	while (str[cmds->utils.i])
	{
		quote_check(str[cmds->utils.i++], &cmds->utils.single_quote,
			&cmds->utils.dble_quote);
		if ((str[cmds->utils.i] == '>' || str[cmds->utils.i] == '<'
				|| str[cmds->utils.i] == ' ') && cmds->utils.dble_quote % 2 == 0
			&& cmds->utils.single_quote % 2 == 0)
			break ;
	}
	*temp = ft_substr(str, start, cmds->utils.i - start);
	del_ind(*&temp);
}

int	take_input(char *str, t_cmds *cmds, int j, int type)
{
	char	*temp;

	cmds->utils.i += 1;
	cmds->utils.single_quote = 0;
	cmds->utils.dble_quote = 0;
	while (str[cmds->utils.i] && str[cmds->utils.i] == ' ')
		cmds->utils.i++;
	if (!str[cmds->utils.i])
	{
		if (type != HEREDOC)
			cmds->input[j] = NULL;
		else
			cmds->heredoc[j] = NULL;
		return (cmds->utils.i);
	}
	take_input_adv(str, cmds, &temp);
	if (type == HEREDOC)
		cmds->heredoc[j] = temp;
	else
		cmds->input[j] = temp;
	return (cmds->utils.i);
}

int	take_input2(char *str, int i)
{
	int		single_quote;
	int		dble_quote;
	char	*temp;
	int		start;
	int		fd;

	i += 1;
	single_quote = 0;
	dble_quote = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	start = i;
	while (str[i] && !(str[i] == ' ' && single_quote % 2 == 0
			&& dble_quote % 2 == 0) && str[i] != '>' && str[i] != '<')
		quote_check(str[i++], &single_quote, &dble_quote);
	temp = ft_substr(str, start, i - start);
	del_ind(&temp);
	fd = open(temp, O_RDONLY);
	free(temp);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	init_take_input(t_cmds	*cmds, char *str)
{
	cmds->utils.i = 0;
	cmds->utils.j = 0;
	cmds->utils.k = 0;
	cmds->utils.single_quote = 0;
	cmds->utils.dble_quote = 0;
	cmds->input = malloc(sizeof(char *) * (input_count(str, 0, 0, 0) + 1));
	if (!cmds->input)
		perror("Malloc!\n");
	cmds->heredoc = malloc(sizeof(char *)
			* (input_count(str, 0, 0, HEREDOC) + 1));
	if (!cmds->heredoc)
		perror("Malloc!\n");
}

void	take_input_first(char *str, t_cmds *cmds)
{
	init_take_input(cmds, str);
	while (str[cmds->utils.i])
	{
		quote_check(str[cmds->utils.i], &cmds->utils.single_quote,
			&cmds->utils.dble_quote);
		if (str[cmds->utils.i] == '<' && cmds->utils.single_quote % 2 == 0
			&& cmds->utils.dble_quote % 2 == 0)
		{
			if (str[cmds->utils.i + 1] && str[cmds->utils.i + 1] == '<')
			{
				cmds->utils.i++;
				cmds->utils.i = take_input(str, cmds, cmds->utils.k, HEREDOC);
				if (cmds->utils.j + cmds->utils.k == (input_count(str, 0, 0, 0)
						+ input_count(str, 0, 0, HEREDOC) - 1))
					cmds->status = status_control(cmds->status, HEREDOC);
				cmds->utils.k++;
			}
			else
				cmds->utils.i = take_input(str, cmds, cmds->utils.j++, 0);
		}
		else
			cmds->utils.i++;
	}
	cmds->input[cmds->utils.j] = NULL;
	cmds->heredoc[cmds->utils.k] = NULL;
}
