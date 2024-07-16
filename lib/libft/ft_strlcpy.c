/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:10:52 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 14:50:58 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*dest;
	char	*sorc;
	size_t	a;

	a = 0;
	dest = dst;
	sorc = (char *)src;
	if (dstsize > 0)
	{
		while (sorc[a] && a < dstsize - 1)
		{
			dest[a] = sorc[a];
			a++;
		}
		dest[a] = '\0';
	}
	a = 0;
	while (src[a])
	{
		a++;
	}
	return (a);
}
