/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:54:59 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 15:55:14 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char		*a;
	size_t		t;

	a = (char *)s;
	t = 0;
	while (t < n)
	{
		if (a[t] == (char)c)
		{
			return (a + t);
		}
		t++;
	}
	return (NULL);
}
