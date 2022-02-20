/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 12:55:56 by esormune          #+#    #+#             */
/*   Updated: 2021/04/29 04:15:27 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	*p;

	p = (char *)str;
	i = 0;
	while (p[i] != '\0')
	{
		if (p[i] == (char)c)
			return (&p[i]);
		i++;
	}
	if (!c && p[i] == '\0')
		return (&p[i]);
	return (NULL);
}
