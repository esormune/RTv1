/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:30:03 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:30:07 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Some basic sphere mathematics first.
** The equation for a sphere is x^2 + y^2 + z^2 = R^2
** where R is a radius and x, y, and z are coordinates
** of point P; therefore P^2 = R^2. With the equation
** of the ray being O + tD (all points of a ray), where
** O is the point of origin, D is the vector and
** t modifies the scale, we get |O + tD|^2 = R^2.
** We can further develop this into:
** O^2 + D^2t^2 + 2ODt − (R^2)0
** which turns into a quadratic function of
** f(x) = ax^2 + bx + c
** In this instance,
** a = D^2
** b = 2OD
** c = O^2 - (R^2)0
** while we solve t for x, since t is the unknown.
** This then can be solved with the following formula:
** delta (discriminant) = b^2−4ac
** x = (−b ± √b^2−4ac) / 2a
** When delta > 0, there are two roots (a + and -), and the
** sphere is intersected in two places.
** If delta == 0, t1 == t2, and it hits in one.
** If delta < 0, there is no intersection.
** If the centre is not origo, it becomes:
** |P − C|^2 − R^2 = 0 ; and:
** a = 1
** b = 2D(O − C)
** c = |O − C|^2 − R^2
*/

/*
** Returns T/F based on if the t is valid. If is valid, will save
** the value into *t.
*/
static t_bool	get_t(double delta, double b, double *t)
{
	double	sqroot;
	double	t1;
	double	t2;

	sqroot = sqrt(delta);
	t1 = (-b + sqroot) / 2.0;
	t2 = (-b - sqroot) / 2.0;
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
	{
		*t = t1;
		return (TRUE);
	}
	else if ((t2 <= t1 && t2 >= 0) || (t1 < 0 && t2 >= 0))
	{
		*t = t2;
		return (TRUE);
	}
	return (FALSE);
}

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
static t_bool	test_intersect(t_ray ray, t_obj *obj, t_vec *poi)
{
	t_vec	vhat;
	double	b;
	double	c;
	double	delta;
	double	t;

	m_apply_ray(&ray, *obj, BWDTSFM);
	vhat = ray.dir;
	vec_normalise(&vhat);
	b = 2.0 * vec_dot(ray.start, vhat);
	c = vec_dot(ray.start, ray.start) - 1.0;
	delta = (b * b) - 4.0 * c;
	if (delta > 0.0)
	{
		if (get_t(delta, b, &t))
		{
			*poi = vec_add(ray.start, vec_scale(vhat, t));
			return (TRUE);
		}
		return (FALSE);
	}
	return (FALSE);
}

/*
** Gets the t, or the point of intersect, for a ray going
** towards a sphere.
*/
t_bool	sphere_t(t_ray ray, t_obj obj, t_point *p)
{
	t_vec	obj_origin;
	t_bool	ret;

	ret = test_intersect(ray, &obj, &p->poi);
	if (!ret)
		return (FALSE);
	m_apply_vec(&p->poi, obj.tform);
	init_vec(&obj_origin);
	m_apply_vec(&obj_origin, obj.tform);
	p->normal = vec_sub(p->poi, obj_origin);
	if (vec_dot(p->normal, ray.dir) > 0.0)
		p->normal = vec_scale(p->normal, -1.0);
	vec_normalise(&p->normal);
	return (TRUE);
}
