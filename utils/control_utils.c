/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:52 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:13:05 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*make_lower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = ft_tolower(str[i]);
	}
	return (str);
}

int	ft_strncmp2(char *dest, char *src)
{
	if ((ft_strncmp(dest, src, ft_strlen(dest)) == 0
			&& ft_strncmp(dest, src, ft_strlen(src)) == 0)
		|| (ft_strncmp(make_lower(dest), src, ft_strlen(dest)) == 0
			&& ft_strncmp(make_lower(dest), src, ft_strlen(src) == 0)))
		return (0);
	return (1);
}

int	status_control(int old, int n)
{
	if (old == 0)
		return (n);
	else if (old == 2 && n == 1)
		return (PIPEHEREDOC);
	else if (old == 3 && n == 1)
		return (PIPEAPPEND);
	else if (old == 4 && n == 1)
		return (PIPEHEREDOCAPPEND);
	else if ((old == 2 && n == 3) || (old == 3 && n == 2))
		return (HEREDOCAPPEND);
	return (n);
}

void	setoldpwd2(char *newpwd, char **newpwd2)
{
	int	i;

	i = ft_strlen(newpwd) - 1;
	if (i > 2 && newpwd[i] == '.'
		&& newpwd[i - 1] == '.' && newpwd[i - 2] == '/')
		*newpwd2 = getcwd(NULL, 0);
	else
		*newpwd2 = NULL;
}

char	*replace_check_dol_adv(t_utils t, char **temp, char *val)
{
	char	*ret;

	ret = malloc(sizeof(char) * (t.i + temp_char_size(temp) \
		+ (temp_size(temp) * 2) + (temp_size(temp)) + 3));
	set_int(&t);
	while (t.i >= 0)
	{
		ret[t.i] = val[t.i];
		t.i--;
	}
	t.i = 0;
	while (temp[t.i])
	{
		ret[t.c++] = '\'';
		while (temp[t.i][t.k])
			ret[t.c++] = temp[t.i][t.k++];
		t.k = 0;
		ret[t.c++] = '\'';
		if (temp[t.i + 1])
			ret[t.c++] = ' ';
		t.i++;
	}
	ret[t.c] = '\0';
	return (ret);
}
