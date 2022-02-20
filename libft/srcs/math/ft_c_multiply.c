/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_multiply.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 17:52:01 by esormune          #+#    #+#             */
/*   Updated: 2021/03/27 17:54:28 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_complex	ft_c_multiply(t_complex a, t_complex b)
{
	t_complex	res;

	res.x = a.x * b.x - a.y * b.y;
	res.y = a.x * b.y + b.x * a.y;
	return (res);
}
