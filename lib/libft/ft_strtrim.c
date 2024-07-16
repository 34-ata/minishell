/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:11:49 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 15:54:12 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	ll;

	ll = 0;
	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set,*s1))
		s1++;
	ll = ft_strlen(s1);
	while (ll && ft_strchr(set, s1[ll - 1]))
		ll--;
	return (ft_substr(s1, 0, ll));
}
