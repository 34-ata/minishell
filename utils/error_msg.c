/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:44:13 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/15 12:30:09 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_error(char	*str)
{
	ft_putstr_fd("near unexpected token '", 2);
	ft_putchar_fd(str[empty_input_output(str, 0, 0)], 2);
	ft_putstr_fd("'\n", 2);
}

void	unset_error_msg(char	*str)
{
	write(2, "minishell: unset: `",
		ft_strlen("minishell: unset: `"));
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n",
		ft_strlen("': not a valid identifier\n"));
	g_globals_exit = 1;
}

void	unset_error(t_cmds	*cmds)
{
	int		i;
	int		j;

	i = 0;
	while (cmds->args[i])
	{
		j = -1;
		while (cmds->args[i][++j])
		{
			if ((!ft_isdigit(cmds->args[i][j])
				&& !ft_isalpha(cmds->args[i][j]))
			&& cmds->args[i][j] != '_')
			{
				unset_error_msg(cmds->args[i]);
				break ;
			}
		}
		if (cmds->args[i][j] == '\0' && j == 0)
		{
			unset_error_msg(cmds->args[i]);
			break ;
		}
		i++;
	}
}

void	ft_msg(char *str, int type)
{
	if (type == ERR_NOT_VALID)
	{
		write(2, "minishell: export: `",
			ft_strlen("minishell: export: `"));
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n",
			ft_strlen("': not a valid identifier\n"));
		g_globals_exit = 1;
	}
}

void	ft_ctrl_d(void)
{
	printf("exit\n");
	exit(0);
}
