/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:59 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:29:59 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** A plane is defined by three points, call these p0, p1, and p2.
** The vector from p0 to p1 will be referred to as ->u, while the
** vector from p0 to p2 will be referenced as ->v. Now, any point
** on this plane can then be calculated by p0 + any scalar multiple
** of vector ->v and any scalar multiple of vector ->u.
** x = p0 + p1 * u + p2 * v
** where u and v represent scalar multiples of their respective vectors.
**
** A line is defined by
** l = a + tk
** where l represents the line, a a point on said line (or "start"),
** t is a scalar quantity, and k is a unit vector.
** Therefore, the point of intersection is defined:
** a + tk = p0 + p1 * u + p2 * v
** or:
**					[t]
** a = [-k  p0  p1] [u]
**					[v]
**
** Since we are working with unit planes (as with our other objects),
** we can define p0 (0, 0, 0), p1 (1, 0, 0), and p2(0, 1, 0)
** and therefore:
** ax = u - kxt
** ay = v - kyt
** az = -kzt
** And thus t = az / -kz. t is thus the scalar for the line for the
** point of intersection. We can also then solve for u and v scalars.
*/

/*
** Solves the quadratic function, returns intersection point
** closest to the camera of t0 or t1 if a hit occurs, otherwise
** returns -1.0. To avoid catastrophic cancellation, we make sure
** the signs are correct by being + if b > 0, - otherwise.
*/

/*
** Returns a T/F based on if there is a valid intersection or not.
** Transforms ray into the local object's space with a backwards
** transform, then uses that info to calculate a possible point of
** interseciton, which it will then save to the *poi.
*/

/*
** Unit plane.
*/
static t_bool	test_intersect(t_ray ray, t_obj *obj, t_vec *poi)
{
	t_vec	k;
	double	u;
	double	v;
	double	t;

	m_apply_ray(&ray, *obj, BWDTSFM);
	k = ray.dir;
	vec_normalise(&k);
	if (close_enough(k.z, 0.0))
		return (FALSE);
	t = ray.start.z / (-k.z);
	if (t < 0.0)
		return (FALSE);
	u = ray.start.x + (k.x * t);
	v = ray.start.y + (k.y * t);
	if ((fabs(u) < 1.0) && (fabs(v) < 1.0))
	{
		*poi = vec_add(ray.start, vec_scale(k, t));
		return (TRUE);
	}
	return (FALSE);
}

/*
** Tests for the intersection for a plane.
*/
t_bool	plane_t(t_ray ray, t_obj obj, t_point *p)
{
	t_vec	origin;
	t_vec	normal;
	t_bool	ret;

	ret = test_intersect(ray, &obj, &p->poi);
	if (!ret)
		return (FALSE);
	m_apply_vec(&p->poi, obj.tform);
	init_vec(&origin);
	vec_set(&normal, 0.0, 0.0, -1.0);
	m_apply_vec(&origin, obj.tform);
	m_apply_vec(&normal, obj.tform);
	p->normal = vec_sub(normal, origin);
	if (vec_dot(p->normal, ray.dir) > 0.0)
		p->normal = vec_scale(p->normal, -1.0);
	vec_normalise(&p->normal);
	return (TRUE);
}
