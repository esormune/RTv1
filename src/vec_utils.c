/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:30:18 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:30:18 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Vector normalisation.
*/
void	vec_normalise(t_vec *v)
{
	double	w;

	w = vec_magn(*v);
	if (w > 0)
	{
		v->x /= w;
		v->y /= w;
		v->z /= w;
	}
}

/*
** Vector magnitude / length of vector.
*/
double	vec_magn(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
** Copies vector.
*/
void	vec_copy(t_vec *from, t_vec *to)
{
	to->x = from->x;
	to->y = from->y;
	to->z = from->z;
}

/*
** Sets points to a vector.
*/
void	vec_set(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

/*
** Nulls a float vector.
*/
void	init_vec(t_vec *v)
{
	v->x = 0.0;
	v->y = 0.0;
	v->z = 0.0;
}
