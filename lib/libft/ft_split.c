/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:09:45 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 15:48:29 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	splitlen(char const *s, char c)
{
	int	a;
	int	t;

	a = 0;
	t = 0;
	while (s[a])
	{
		if ((s[a] == c && s[a + 1]) && a != 0)
			t++;
		a++;
	}
	return (t + 1);
}

static void	ft_allc(char **tab, char const *s, char sep)
{
	char		**ret;
	char const	*temp;

	temp = s;
	ret = tab;
	while (*temp)
	{
		while (*s == sep)
			++s;
		temp = s;
		while (*temp && *temp != sep)
			++temp;
		if (temp > s)
		{
			*ret = ft_substr(s, 0, temp - s);
			s = temp;
			++ret;
		}
	}
	*ret = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		size;

	if (!s)
		return (NULL);
	size = splitlen(s, c);
	ret = malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	ft_allc(ret, s, c);
	return (ret);
}
