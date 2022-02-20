/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:53 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:29:54 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Because of the way we are implementing unit cylinders and transforming
** them from the local coordinate to the global coordinates,
** we treat all cylinders as a "circle" lying on the x/y axis,
** and pay attention to z only in regarding to the height.
** So, in checking the circle we can use the formula:
** line l = p + tv
** circle x^2 + y^2 = r^2
** which, when filled, turns to
** (px + tvx)^2 +(py + tvy)^2 = r^2
** and eventually expands to a quadratic formula
** at^2 + bt + c = 0
** where
** a = vx^2 + vy^2
** b = 2(pxvx + pyvy)
** c = (px)^2 + (py)^2 - r^2
** and t is solved t = (−b ± √b^2−4ac) / 2a
** Then, if the absolute value of z is between 0 and 1, the z will also match
** and there is an intersection.
*/

/*
** Returns which t in the array is closest and saves closest value.
*/
static int	cc_get_closest(double *t)
{
	int		index;
	int		i;
	double	min;

	i = 0;
	index = 0;
	min = 10e6;
	while (i < 4)
	{
		if (t[i] < min)
		{
			min = t[i];
			index = i;
		}
		i++;
	}
	return (index);
}

/*
** Sets the validity of the distances t based on if the intersection
** hits the object. All valids are initially FALSE. The first check
** means that sqrt > 0.0 and therefore t's are set with valid
** values. Second check means that close_enough function returned
** false previously and the ts have testable values.
*/
static void	check_valid(t_vec *poi, double *t, t_bool *t_valid)
{
	int	i;

	if (t[0] != IGNORE)
	{
		if (t[0] > 0.0 && (fabs(poi[0].z) < 1.0))
			t_valid[0] = TRUE;
		if (t[1] > 0.0 && (fabs(poi[1].z) < 1.0))
			t_valid[1] = TRUE;
	}
	if (t[2] != IGNORE)
	{
		if (t[2] > 0.0 && (sqrtf(pow(poi[2].x, 2.0)
					+ pow(poi[2].y, 2.0)) < 1.0))
			t_valid[2] = TRUE;
		if (t[3] > 0.0 && (sqrtf(pow(poi[3].x, 2.0)
					+ pow(poi[3].y, 2.0)) < 1.0))
			t_valid[3] = TRUE;
	}
	i = 0;
	while (i < 4)
	{
		if (t_valid[i] == FALSE)
			t[i] = IGNORE;
		i++;
	}
}

static int	get_t(t_quadratic q, t_vec v, t_ray ray, t_vec *s_poi)
{
	t_vec	poi[4];
	double	t[4];
	t_bool	t_valid[4];
	int		closest;

	t_valid[0] = FALSE;
	t_valid[1] = FALSE;
	t_valid[2] = FALSE;
	t_valid[3] = FALSE;
	cc_calc_t(q, t, v, ray);
	cc_calc_poi(poi, t, v, ray);
	check_valid(poi, t, t_valid);
	if (!t_valid[0] && !t_valid[1] && !t_valid[2] && !t_valid[3])
		return (-1);
	closest = cc_get_closest(t);
	*s_poi = poi[closest];
	return (closest);
}

/*
** First checks for validity of the actual circular
** cylinder, and then for the cone endings. Saves these results
** to 4 t values and 4 points of intersections, and then
** calculates which is closest. If none intersect, returns false;
** otherwise closest is saved into *save. The v carries the value of z
** which will have to have an abs value between 1.0 and 0.0 to fit
** the unit cylinder. Returns -1 if no valid intersection, otherwise
** returns which value of t it was for proper normal calculation
** (whether to calculate cylinder or circle).
*/
/*
** Returns a T/F based on if there is a valid intersection or not.
** Transforms ray into the local object's space with a backwards
** transform, then uses that info to calculate a possible point of
** interseciton, which it will then save to the *poi.
*/
static int	test_intersect(t_ray ray, t_obj *obj, t_vec *poi, t_vec *v)
{
	t_quadratic	q;

	m_apply_ray(&ray, *obj, BWDTSFM);
	*v = ray.dir;
	vec_normalise(v);
	q.a = pow(v->x, 2.0) + pow(v->y, 2.0);
	q.b = 2.0 * (ray.start.x * v->x + ray.start.y * v->y);
	q.c = pow(ray.start.x, 2.0) + pow(ray.start.y, 2.0) - 1.0;
	q.sqroot = sqrtf(pow(q.b, 2.0) - 4 * q.a * q.c);
	return (get_t(q, *v, ray, poi));
}

/*
** Gets the t, or the point of intersect, for a ray going
** towards a cylinder.
*/
t_bool	cylinder_t(t_ray ray, t_obj obj, t_point *p)
{
	t_vec	v;
	int		closest;

	closest = test_intersect(ray, &obj, &p->poi, &v);
	if (closest < 0)
		return (FALSE);
	if (closest == 0 || closest == 1)
		return (cc_area_intersect(obj, p));
	else
	{
		if (!close_enough(v.z, 0.0))
		{
			if (sqrtf(pow(p->poi.x, 2.0) + pow(p->poi.y, 2.0)) < 1.0)
				return (cc_base_intersect(obj, p));
			return (FALSE);
		}
		return (FALSE);
	}
}
