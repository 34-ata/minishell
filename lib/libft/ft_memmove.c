/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:49:41 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 16:22:05 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*sorc;

	dest = dst;
	sorc = src;
	if (len == 0 || dst == src)
		return (dest);
	if (dst < src)
	{
		while (len > 0)
		{
			*dest++ = *sorc++;
			len--;
		}
	}
	if (dst > src)
	{
		while (len > 0)
		{
			len--;
			dest[len] = sorc[len];
		}
	}
	return (dst);
}
