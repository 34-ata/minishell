/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:10:09 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 14:52:51 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*s1)
{
	size_t	size;
	char	*dest;

	size = ft_strlen(s1) + 1;
	dest = malloc(size);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, size);
	return (dest);
}
