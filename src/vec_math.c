/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:30:14 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:30:14 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Vector cross product.
*/
t_vec	vec_cross(t_vec a, t_vec b)
{
	t_vec	x;

	x.x = a.y * b.z - a.z * b.y;
	x.y = a.z * b.x - a.x * b.z;
	x.z = a.x * b.y - a.y * b.x;
	return (x);
}

/*
** Vector dot product.
*/
double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
** Vector scaling.
*/
t_vec	vec_scale(t_vec a, double scale)
{
	a.x *= scale;
	a.y *= scale;
	a.z *= scale;
	return (a);
}

/*
** Vector addition.
*/
t_vec	vec_add(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

/*
** Vector subtraction.
*/
t_vec	vec_sub(t_vec a, t_vec b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}
