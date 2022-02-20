/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 13:15:27 by esormune          #+#    #+#             */
/*   Updated: 2021/04/29 04:02:14 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*p;

	i = ft_strlen(str) + 1;
	p = (char *)str;
	while (i--)
	{
		if (p[i] == (char)c)
			return (&p[i]);
	}
	return (NULL);
}
