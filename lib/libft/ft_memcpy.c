/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:53:20 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 15:54:23 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	a;

	a = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (a < n)
	{
		((char *)dst)[a] = ((char *)src)[a];
		a++;
	}
	return (dst);
}
