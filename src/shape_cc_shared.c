/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cc_shared.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:16 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:29:16 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Contains functions that are used by both
** cone and cylinder calculations with minor
** differences.
*/

void	cc_calc_t(t_quadratic q, double *t, t_vec v, t_ray ray)
{
	if (q.sqroot > 0.0)
	{
		t[0] = (-q.b + q.sqroot) / (2.0 * q.a);
		t[1] = (-q.b - q.sqroot) / (2.0 * q.a);
	}
	else
	{
		t[0] = IGNORE;
		t[1] = IGNORE;
	}
	if (close_enough(v.z, 0.0))
	{
		t[2] = IGNORE;
		t[3] = IGNORE;
	}
	else
	{
		t[2] = (ray.start.z - 1.0) / -v.z;
		t[3] = (ray.start.z + 1.0) / -v.z;
	}
}

void	cc_calc_poi(t_vec *poi, double *t, t_vec v, t_ray ray)
{
	if (t[0] != IGNORE)
	{
		poi[0] = vec_add(ray.start, vec_scale(v, t[0]));
		poi[1] = vec_add(ray.start, vec_scale(v, t[1]));
	}
	if (t[2] != IGNORE)
	{
		poi[2] = vec_add(ray.start, vec_scale(v, t[2]));
		poi[3] = vec_add(ray.start, vec_scale(v, t[3]));
	}
}

t_bool	cc_area_intersect(t_obj obj, t_point *p)
{
	t_vec	org_normal;
	t_vec	obj_origin;

	init_vec(&obj_origin);
	m_apply_vec(&obj_origin, obj.tform);
	if (obj.shape == CYLINDER)
		vec_set(&org_normal, p->poi.x, p->poi.y, 0.0);
	else
	{
		vec_set(&org_normal, p->poi.x, p->poi.y,
			(-sqrtf(pow(p->poi.x, 2.0) + pow(p->poi.y, 2.0))));
	}
	m_apply_vec(&p->poi, obj.tform);
	m_apply_vec(&org_normal, obj.tform);
	p->normal = vec_sub(org_normal, obj_origin);
	vec_normalise(&p->normal);
	return (TRUE);
}

t_bool	cc_base_intersect(t_obj obj, t_point *p)
{
	t_vec	org_normal;
	t_vec	obj_origin;

	init_vec(&obj_origin);
	m_apply_vec(&obj_origin, obj.tform);
	if (obj.shape == CYLINDER)
		vec_set(&org_normal, 0.0, 0.0, p->poi.z);
	else
		vec_set(&org_normal, 0.0, 0.0, 1.0);
	m_apply_vec(&p->poi, obj.tform);
	m_apply_vec(&org_normal, obj.tform);
	p->normal = vec_sub(org_normal, obj_origin);
	vec_normalise(&p->normal);
	return (TRUE);
}
