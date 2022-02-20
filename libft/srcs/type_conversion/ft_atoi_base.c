/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:07:31 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 21:55:55 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_save(char *num, int base, int i)
{
	long	res;
	int		x;
	char	*str;

	res = 0;
	str = "0123456789ABCDEF";
	while (num[i] != '\0' && (ft_isalnum(num[i])))
	{
		x = 0;
		while (str[x] != num[i] && x < base)
			x++;
		if (x >= base)
			return (0);
		res = res * base + x;
		i++;
	}
	return (res);
}

int	ft_atoi_base(char *str, int base)
{
	int		i;

	if (base < 2 || base > 16)
		return (0);
	if (base == 10)
		return (ft_atoi(str));
	ft_toupper_str(str);
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' \
		|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (!ft_isalnum(str[i]))
		return (0);
	return (ft_save(str, base, i));
}
