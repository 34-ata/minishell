/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vb_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:54:52 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/11 18:12:47 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	del_ind_adv(char **s, int *rm1, int *rm2, int *i)
{
	if (*rm1 != -1 && *rm2 != -1)
	{
		ft_remove_char_by_index(&*s, *rm1);
		ft_remove_char_by_index(&*s, *rm2 - 1);
		*i = *i - 2;
		*rm1 = -1;
		*rm2 = -1;
		if (*i == -2)
			*i = -1;
	}
}

void	del_ind_int(int *rm1, int *rm2, int *i, int *quote)
{
	*rm1 = -1;
	*rm2 = -1;
	*i = 0;
	*quote = 0;
}
