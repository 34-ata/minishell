/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:44:08 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/14 16:17:08 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_cmmn(char *input, char *lll)
{
	if (!input || !lll)
		return (1);
	if (ft_strncmp(input, lll, ft_strlen(input)) == 0 \
	&& ft_strncmp(input, lll, ft_strlen(lll)) == 0)
		return (0);
	return (1);
}

void	error_write(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
}
