/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:12 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:29:12 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Sets the rgb values for the channels.
*/
static void	set_pixel(t_img *img, uint32_t x, uint32_t y, t_colour c)
{
	uint32_t	i;

	if (x > img->channels->w || y > img->channels->h)
		return ;
	i = (img->channels->w * y) + x;
	img->channels->r[i] = c.r;
	img->channels->g[i] = c.g;
	img->channels->b[i] = c.b;
}

static void	set_closest(t_scene *scene, int *closest_obj, int current_obj)
{
	*closest_obj = current_obj;
	scene->closest.poi = scene->current.poi;
	scene->closest.normal = scene->current.normal;
	scene->closest.colour = scene->objs[current_obj].colour;
}

/*
** Uses a ray from the camera into the pixel point and checks
** for an intersection with any objects in the scene.
*/
static t_bool	check_intersect(t_img *img, t_ray ray, int *closest_obj)
{
	int		i;
	double	min_dist;
	double	dist;
	t_bool	does_intersect;

	i = 0;
	does_intersect = FALSE;
	min_dist = 1e6;
	while (i < img->scene.objcount)
	{
		if (img->scene.objs[i].get_t(ray, img->scene.objs[i],
				&img->scene.current))
		{
			does_intersect = TRUE;
			dist = vec_magn(vec_sub(img->scene.current.poi, ray.start));
			if (dist < min_dist)
			{
				min_dist = dist;
				set_closest(&img->scene, closest_obj, i);
			}
		}
		i++;
	}
	return (does_intersect);
}

void	render(t_img *img)
{
	uint32_t	x;
	uint32_t	y;
	t_ray		ray;
	int			closest_obj;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			ray = ray_gen_cam(img, x, y);
			if (check_intersect(img, ray, &closest_obj))
			{
				img->scene.raycount = 0;
				if (compute_colour(&img->scene, &img->scene.closest,
						ray, closest_obj))
					set_pixel(img, x, y, img->scene.closest.colour);
			}
			x++;
		}
		y++;
	}
	draw_image(img, img->channels);
}
