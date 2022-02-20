/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:04 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:29:05 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Prints light for debugging.
*/
void	print_light(t_light *l)
{
	print_vec(l->pos);
	ft_printf("r %.3f g %.3f b %.3f\n", l->colour.r, l->colour.g,
		l->colour.b);
	ft_printf("intensity %.3f\n", l->intensity);
}

/*
** Debug print vector.
*/
void	print_vec(t_vec v)
{
	ft_printf("vector: %.3lf, %.3lf, %.3lf\n", v.x, v.y, v.z);
}

/*
** Debug print pixel.
*/
void	print_pixel(t_pixel p)
{
	ft_printf("pixel: x %d, y %d\n", p.x, p.y);
}

/*
** Debug colour.
*/
void	print_colour(t_colour c)
{
	ft_printf("colour: r %.3lf, g %.3lf, b %.3lf\n", c.r, c.g, c.b);
}

/*
** Prints object for debugging.
*/
void	print_obj(t_obj obj)
{
	ft_printf("............\n");
	ft_printf("shape: %d\n", obj.shape);
	ft_printf("trans: %.3lf, %.3lf, %.3lf\n", obj.trans.x,
		obj.trans.y, obj.trans.z);
	ft_printf("scale: %.3lf, %.3lf, %.3lf\n", obj.scale.x,
		obj.scale.y, obj.scale.z);
	ft_printf("rot: %.3lf, %.3lf, %.3lf\n", obj.rot.x,
		obj.rot.y, obj.rot.z);
	ft_printf("r %.3f g %.3f b %.3f\n", obj.colour.r,
		obj.colour.g, obj.colour.b);
}
