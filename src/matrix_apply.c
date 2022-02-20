/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_apply.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:19 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:19 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Applies a matrix transformation to a vector.
*/
void	m_apply_vec(t_vec *vec, t_matrix m)
{
	t_vec4	temp;
	t_vec4	ret;

	temp.x = vec->x;
	temp.y = vec->y;
	temp.z = vec->z;
	temp.w = 1.0;
	ret = m_multiply_vec(m, temp);
	vec->x = ret.x;
	vec->y = ret.y;
	vec->z = ret.z;
}

/*
** Applies a matrix transformation to a ray.
*/
void	m_apply_ray(t_ray *ray, t_obj obj, t_bool flag)
{
	if (flag == FWDTSFM)
	{
		m_apply_vec(&ray->start, obj.tform);
		m_apply_vec(&ray->end, obj.tform);
	}
	else
	{
		m_apply_vec(&ray->start, obj.inv);
		m_apply_vec(&ray->end, obj.inv);
	}
	ray->dir = vec_sub(ray->end, ray->start);
}
