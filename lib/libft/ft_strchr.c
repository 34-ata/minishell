/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:10:03 by fuyar             #+#    #+#             */
/*   Updated: 2024/07/04 16:17:37 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	slen;

	slen = ft_strlen(s);
	while (slen >= 0)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		slen--;
		s++;
	}
	return (NULL);
}
