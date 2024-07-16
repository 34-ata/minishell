/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:25:40 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/15 12:25:33 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_valid_pipe(char *str, int single_quote, int dble_quote, int count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] == '|' && (single_quote % 2 == 0 && dble_quote % 2 == 0))
			count += 1;
		i++;
	}
	return (count);
}

void	init_res(char ***res, char *str)
{
	(*res) = malloc(sizeof(char *) * (count_valid_pipe(str, 0, 0, 0) + 2));
	if ((*res) == NULL)
		perror("malloc failed");
	(*res)[count_valid_pipe(str, 0, 0, 0) + 1] = NULL;
}

char	**quot_split(char *str, int single_quote, int dble_quote, int start)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	init_res(&res, str);
	while (str[i])
	{
		quote_check(str[i], &single_quote, &dble_quote);
		if (str[i] == '|' && (single_quote % 2 == 0 && dble_quote % 2 == 0))
		{
			res[j] = ft_substr(str, start, i - start);
			start = i + 1;
			j++;
		}
		i++;
	}
	if (j == 0)
		res[j] = ft_strdup(str);
	else if (j <= count_valid_pipe(str, 0, 0, 0))
		res[j] = ft_substr(str, start, i - start);
	return (res);
}

void	continue_(t_cmds *cmds, char *temp_args, t_main_env *env)
{
	char	**args;

	check_dollar(cmds, &temp_args, 0, 0);
	args = quot_split(temp_args, 0, 0, 0);
	free(temp_args);
	parse_args(args, cmds, env);
	cleanlist(cmds);
}

void	start_parsing(char	**envp, char	*temp, char	*temp_args, char **av)
{
	t_main_env	*env;
	t_cmds		cmds;

	env = set_env_main(av);
	take_env(&cmds, env, 0, envp);
	cmds.env = 0;
	while (1)
	{
		set_signal(MAIN_P);
		init_env(env, &cmds);
		take_env(&cmds, env, 1, NULL);
		temp = readline("minishell$> ");
		add_history(temp);
		temp_args = ft_strtrim(temp, " \t");
		free(temp);
		if (!temp_args)
			ft_ctrl_d();
		if (!arg_control(temp_args))
		{
			free (temp_args);
			freecpointer(cmds.envr);
			continue ;
		}
		continue_(&cmds, temp_args, env);
	}
}
