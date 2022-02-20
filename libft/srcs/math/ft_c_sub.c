/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:52:37 by esormune          #+#    #+#             */
/*   Updated: 2021/05/05 14:53:40 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_complex	ft_c_sub(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	return (res);
}
