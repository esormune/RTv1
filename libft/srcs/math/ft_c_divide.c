/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_divide.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 18:07:33 by esormune          #+#    #+#             */
/*   Updated: 2021/04/20 17:07:13 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_complex	ft_c_divide(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = (a.x * b.x + a.y * b.y) / (b.x * b.x + b.y * b.y);
	res.y = (-a.x * b.y + b.x * a.y) / (b.x * b.x + b.y * b.y);
	return (res);
}
