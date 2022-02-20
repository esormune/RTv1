/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:14 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:15 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Computes the colour for a material. Checks for shininess
** and reflectivity. Returns a T/F based on if there is illumination
** on an object and therefore cause to colour the pixel.
** Reflectivity and shine functions to be added in RT.
*/
t_bool	compute_colour(t_scene *s, t_point *closest, t_ray ray, int obj)
{
	t_bool		illumination;

	(void)ray;
	illumination = light_check(s, closest, obj);
	if (!illumination)
		return (FALSE);
	colour_check_max(&s->max, closest->colour);
	return (TRUE);
}
