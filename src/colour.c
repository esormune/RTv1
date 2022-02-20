/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:23:02 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:23:03 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Nulls a colour struct.
*/
void	init_colour(t_colour *c)
{
	c->r = 0.0;
	c->g = 0.0;
	c->b = 0.0;
	c->a = 0.0;
}

/*
** Converts rgb values into a uint32_t colour.
*/
int	ft_colour(int r, int g, int b)
{
	return ((r * 65536) + (g * 256) + b);
}

/*
** Sets a colour struct with rgb values.
*/
void	colour_fset(t_colour *c, double r, double g, double b)
{
	c->r = r;
	c->g = g;
	c->b = b;
	c->a = 0.0;
}

/*
** Sets a colour struct with rgb values where
** they are limited between 0.0 and 1.0.
*/
void	colour_fset_clamp(t_colour *c, double r, double g, double b)
{
	c->r = ft_clamp_d(r, 0.0, 1.0);
	c->g = ft_clamp_d(g, 0.0, 1.0);
	c->b = ft_clamp_d(b, 0.0, 1.0);
	c->a = 0.0;
}

/*
** Checks for colour max values. If any of the new colours
** are higher than what's already saved, will set the values
** as the new ones.
*/
void	colour_check_max(t_colour *max, t_colour c)
{
	if (c.r > max->r)
		max->r = c.r;
	if (c.g > max->g)
		max->g = c.g;
	if (c.b > max->b)
		max->b = c.b;
}
