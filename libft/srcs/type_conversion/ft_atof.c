/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:54:57 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:54:57 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_atof_dec(const char *str, int i)
{
	int			exp;
	int			j;
	size_t		integer;
	long double	ret;

	exp = 0;
	ret = 0.0;
	if (str[i] != '.')
		return (ret);
	i++;
	j = i;
	while (str[j] != '\0' && (str[j] >= 48 && str[j] <= 57))
	{
		exp++;
		j++;
	}
	integer = ft_atoi_sizet(&str[i]);
	if (integer)
		ret = ft_neg_pow_ten(integer, exp);
	return (ret);
}

long double	ft_atof(const char *str)
{
	long double	res;
	int			i;
	int			negcoef;

	i = 0;
	res = 0;
	negcoef = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' \
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		negcoef = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] < 48 || str[i] > 57)
		return (0);
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return ((res + (ft_atof_dec(str, i))) * negcoef);
}
