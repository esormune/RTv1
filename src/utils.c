/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:30:10 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:30:11 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Checks whether or not two floating point numbers are
** within a close enough range defined by the machine epsilon.
*/
t_bool	close_enough(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (TRUE);
	return (FALSE);
}

/*
** Turns degrees to radians.
*/
double	d_to_rad(int deg)
{
	double	clamp;

	clamp = ft_clamp_d(deg, 0, 360);
	return (clamp * (PI / 180.0f));
}
