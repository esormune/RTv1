/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:08 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:29:08 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Copies a ray.
*/
void	ray_copy(t_ray *from, t_ray *to)
{
	vec_copy(&from->start, &to->start);
	vec_copy(&from->end, &to->end);
	vec_copy(&from->dir, &to->dir);
}

/*
** Generates a ray from start point to end point.
*/
t_ray	ray_gen(t_vec start, t_vec end)
{
	t_ray	new;

	new.start = start;
	new.end = end;
	new.dir = vec_sub(new.end, new.start);
	return (new);
}

/*
** Generates a ray from camera start to the pixel point given on
** screen space.
*/
t_ray	ray_gen_cam(t_img *img, int x, int y)
{
	t_ray	ray;
	t_vec	screen_point;
	t_vec	world_point;
	double	norm_x;
	double	norm_y;

	norm_x = (double)x * img->x_fact - 1.0;
	norm_y = (double)y * img->y_fact - 1.0;
	screen_point = vec_add(img->scene.camera.centre,
			vec_scale(img->scene.camera.u, norm_x));
	world_point = vec_add(screen_point, vec_scale(img->scene.camera.v, norm_y));
	ray.start = img->scene.camera.pos;
	ray.end = world_point;
	ray.dir = vec_sub(ray.end, ray.start);
	return (ray);
}
