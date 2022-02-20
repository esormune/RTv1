/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:22:51 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:22:56 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Initialises the camera struct.
*/
void	init_camera(t_camera *cam)
{
	init_vec(&cam->pos);
	init_vec(&cam->look_at);
	init_vec(&cam->up);
	init_vec(&cam->u);
	init_vec(&cam->v);
	init_vec(&cam->centre);
	init_vec(&cam->alignment);
	cam->length = 1.0;
	cam->horizon = 0.25;
	cam->aspect_ratio = 16.0 / 9.0;
	cam->pos.y = -10;
	cam->pos.z = -2.0;
	cam->up.z = 1.0;
}

/*
** Updates camera geometry.
*/
void	camera_update(t_camera *cam)
{
	cam->alignment = vec_sub(cam->look_at, cam->pos);
	vec_normalise(&cam->alignment);
	if (cam->alignment.x == 0 && cam->alignment.y == 0 && cam->alignment.z == 1)
		vec_set(&cam->up, 0.0, 1.0, 0.0);
	cam->u = vec_cross(cam->alignment, cam->up);
	vec_normalise(&cam->u);
	cam->v = vec_cross(cam->u, cam->alignment);
	vec_normalise(&cam->v);
	cam->centre = vec_add(cam->pos, (vec_scale(cam->alignment, cam->length)));
	cam->u = vec_scale(cam->u, cam->horizon);
	cam->v = vec_scale(cam->v, (cam->horizon / cam->aspect_ratio));
}
