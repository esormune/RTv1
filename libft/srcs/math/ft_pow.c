/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:00:06 by esormune          #+#    #+#             */
/*   Updated: 2021/03/25 23:49:32 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_pow(int nb, int pow)
{
	int			i;
	long double	res;

	if (pow == 0)
		return (1);
	i = pow;
	res = (long double)nb;
	while (i > 1)
	{
		res = res * nb;
		i--;
	}
	return (res);
}
