/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:11:19 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 14:50:29 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned long	a;
	unsigned long	size;
	char			*ret;

	a = 0;
	size = ft_strlen(s);
	ret = malloc(sizeof(char) * size + 1);
	if (!ret)
		return (NULL);
	while (s[a])
	{
		ret[a] = f(a, s[a]);
		a++;
	}
	ret[a] = '\0';
	return (ret);
}
