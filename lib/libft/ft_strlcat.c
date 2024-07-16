/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:10:43 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 16:49:38 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	ds;
	size_t	ss;

	ds = ft_strlen(dst);
	ss = ft_strlen((char *)src);
	a = 0;
	if (dstsize <= ds)
		return (ss + dstsize);
	while (src[a] && ds + a + 1 < dstsize)
	{
		dst[ds + a] = src[a];
		a++;
	}
	dst[ds + a] = '\0';
	return (ds + ss);
}
