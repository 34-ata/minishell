/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:44:08 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 18:08:18 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_behind(char *av)
{
	int	i;
	int	c;
	int	k;

	i = 0;
	c = 0;
	k = 0;
	while (av[i])
	{
		if (av[i] == '.')
			c++;
		if (c == 2)
		{
			k += 1;
			c = 0;
		}
		if (av[i] == '/')
			c = 0;
		i++;
	}
	return (k);
}

char	*get_clear_cwd(char *cwd, int c)
{
	int		i;

	if (c == 0)
		return (NULL);
	cwd = getcwd(NULL, 0);
	i = ft_strlen(cwd) - 1;
	while (cwd[i])
	{
		if (cwd[i] != '/')
			i--;
		if (cwd[i] == '/')
		{
			c -= 1;
			cwd[i + 1] = '\0';
			i--;
		}
		if (c == 0)
			break ;
	}
	return (cwd);
}

char	*get_clear_pwd(char *cwd, int c)
{
	int	i;

	if (c == 0)
		return (NULL);
	i = 0;
	while (cwd[i])
	{
		if (cwd[i] != '/')
			i++;
		if (cwd[i] == '/')
		{
			c -= 1;
			i++;
		}
		if (c == 0)
			break ;
	}
	return (cwd + i);
}

char	*edit_pwd(char *av)
{
	char	*pwd;
	char	*ret;

	pwd = getcwd(NULL, 0);
	ret = ft_strjoin(pwd, (av + 1));
	free(pwd);
	return (ret);
}

void	patherror1(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	g_globals_exit = 127;
	exit(127);
}
