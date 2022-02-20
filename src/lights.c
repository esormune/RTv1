/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:05 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:06 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Checks whether or not the light is between the object and the poi,
** in which case there is an intersection but a false shadow & corrects that.
** If the distance between the new light's poi is shorter than the distance
** to the obj poi, then we have a false positive. Also checks for the instance
** that the intersections are the same point, in which it will negate the
** shadow and be resolved by simple z-fighting.
*/
static t_bool	check_valid_shadow(t_vec l_poi, t_vec obj_poi, t_vec l_pos)
{
	double	dist;
	double	ldist;

	if (close_enough(l_poi.x, obj_poi.x) && close_enough(l_poi.y, obj_poi.y)
		&& close_enough(l_poi.z, obj_poi.z))
		return (FALSE);
	ldist = vec_magn(vec_sub(l_pos, obj_poi));
	dist = vec_magn(vec_sub(l_poi, obj_poi));
	if (dist >= ldist)
		return (FALSE);
	return (TRUE);
}

static t_bool	check_for_shadow(t_scene *s, int i, t_point *p, t_light *light)
{
	t_point	new;
	t_ray	ray;
	t_bool	valid_int;
	t_vec	ldir;

	init_point(&new);
	ldir = vec_sub(light->pos, p->poi);
	vec_normalise(&ldir);
	ray = ray_gen(p->poi, vec_add(p->poi, ldir));
	valid_int = s->objs[i].get_t(ray, s->objs[i], &new);
	if (valid_int)
		valid_int = check_valid_shadow(new.poi, p->poi, light->pos);
	if (valid_int)
		return (TRUE);
	return (FALSE);
}

/*
** Checks for illumination of a point in the world by drawing a ray from
** the point of intersection to the light. Loops through all objects and
** if the ray hits another object, a shadow is cast and there will be no
** illumination on the point. Otherwise, intensity is calculated. Takes
** in integer for current object.
*/
double	light_check_illum(t_scene *s, int cur_obj, t_light *light, t_point *p)
{
	t_vec	ldir;
	double	angle;
	t_bool	valid_intersect;
	int		i;

	i = 0;
	ldir = vec_sub(light->pos, p->poi);
	vec_normalise(&ldir);
	while (i < s->objcount)
	{
		if (i != cur_obj)
		{
			valid_intersect = check_for_shadow(s, i, p, light);
			if (valid_intersect)
				return (0.0);
		}
		i++;
	}
	angle = acos(vec_dot(p->normal, ldir));
	if (angle < HALF_PI)
		return (light->intensity * (1.0 - (angle / HALF_PI)));
	return (0.0);
}

/*
** After finding the closest point of intersection, this function will
** check for illumination, returning a T/F boolean. It will loop through
** all lights to gather the correct intensity of rgb values between 0.0-1.0
** and then use this multiplier to later calculate the rgb values and save
** them to the"closest" value in the scene struct.
*/
t_bool	light_check(t_scene *s, t_point *closest, int obj)
{
	int			j;
	t_colour	c;
	double		illumination;
	t_bool		illum_found;

	j = 0;
	illum_found = FALSE;
	init_colour(&c);
	while (j < s->lcount)
	{
		illumination = light_check_illum(s, obj, &s->lights[j], closest);
		if (illumination)
		{
			illum_found = TRUE;
			c.r += (s->lights[j].colour.r * illumination);
			c.g += (s->lights[j].colour.g * illumination);
			c.b += (s->lights[j].colour.b * illumination);
		}
		j++;
	}
	if (!illum_found)
		return (FALSE);
	colour_fset(&closest->colour, (closest->colour.r * c.r),
		(closest->colour.g * c.g), (closest->colour.b * c.b));
	return (TRUE);
}
