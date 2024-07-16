/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faata <faata@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:44:08 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 17:38:03 by faata            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_value(char *val)
{
	int	i;

	i = 0;
	while (val[i])
	{
		if (ft_strchr("|<>", val[i]))
			return (i);
		i++;
	}
	return (-1);
}

int	temp_size(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
		i++;
	return (i);
}

int	temp_char_size(char **temp)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (temp[i])
		res += ft_strlen(temp[i++]);
	return (res);
}

void	set_int(t_utils *t)
{
	t->c = t->i;
	t->k = 0;
}

char	*replace_check_dol(char *val)
{
	char	*ret;
	char	**temp;
	t_utils	t;

	t.i = check_value(val);
	if (t.i == -1)
		return (NULL);
	temp = ft_split(val + t.i, ' ');
	ret = replace_check_dol_adv(t, temp, val);
	freecpointer(temp);
	return (ret);
}
