/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:52 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:38:41 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	g_globals_exit;

void	errorm(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	ft_remove_char_by_index(char **str, int index)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !*str)
		return ;
	if (index < 0 || index > (int)ft_strlen(*str))
		return ;
	new = (char *)malloc(ft_strlen(*str));
	if (!new)
		return ;
	while ((*str)[i])
	{
		if (i != index)
		{
			new[j] = (*str)[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	free(*str);
	*str = new;
}

void	del_ind(char **str)
{
	char	*s;
	int		quote;
	int		i;
	int		rm1;
	int		rm2;

	del_ind_int(&rm1, &rm2, &i, &quote);
	s = ft_strdup(*str);
	while (s[i])
	{
		if (quote == 0 && (s[i] == '\"' || s[i] == '\''))
		{
			rm1 = i;
			quote = (int)s[i];
		}
		else if (s[i] == quote)
		{
			rm2 = i;
			quote = 0;
		}
		del_ind_adv(&s, &rm1, &rm2, &i);
		i++;
	}
	free(*str);
	*str = s;
}

char	*set_dollar_zero(char **av, int a)
{
	char	*maincwd;
	char	*mainpwd;
	char	*lastpwd;

	lastpwd = NULL;
	a = check_behind(av[0]);
	if (a != 0)
	{
		maincwd = get_clear_cwd(NULL, a);
		mainpwd = get_clear_pwd(av[0], a);
		lastpwd = ft_strjoin(maincwd, mainpwd);
		free(maincwd);
	}
	else if (ft_strncmp2(av[0], "./minishell"))
		lastpwd = edit_pwd(av[0]);
	else
		return (ft_strdup(av[0]));
	return (lastpwd);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 1)
		errorm("Error: too many arguments!\n");
	g_globals_exit = 0;
	start_parsing(envp, NULL, NULL, av);
}
