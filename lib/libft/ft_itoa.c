/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fuyar <fuyar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:56:24 by fuyar             #+#    #+#             */
/*   Updated: 2023/10/12 16:45:11 by fuyar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlenn(int x)
{
	int	a;

	a = 0;
	if (x == -2147483648)
		return (11);
	if (x < 0)
	{
		a++;
		x = -x;
	}
	while (x > 0)
	{
		x = x / 10;
		a++;
	}
	return (a);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		a;
	int		size;

	size = intlenn(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ret = malloc(size + 1);
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		ret[0] = '-';
		n = -n;
	}
	a = size;
	while (n > 0 && a--)
	{
		ret[a] = '0' + (n % 10);
		n = n / 10;
	}
	ret[size] = '\0';
	return (ret);
}
