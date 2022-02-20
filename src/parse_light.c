/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:53 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:53 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Parses light information. Checks that there is enough
** allocated space for the light to be put in.
** If the size of the array does not
** match all required fields, returns a default light.
*/
void	parse_light(char **words, t_scene *s, t_flags *flags)
{
	int	max;

	flags->lights++;
	if (flags->lights > s->lcount)
		ft_getout("Invalid number of lights.");
	if (s->at_light >= s->lcount)
		ft_getout("Invalid number of lights.");
	max = ft_get_arr_size(words);
	if (max != LIGHT_PARAMS)
		ft_getout("Invalid number of parameters for light.");
	vec_set(&s->lights[s->at_light].pos, ft_atof(words[1]),
		ft_atof(words[2]), ft_atof(words[3]));
	s->lights[s->at_light].intensity = ft_clamp_d(ft_atof(words[4]), 0.0, 1.0);
	colour_fset_clamp(&s->lights[s->at_light].colour, ft_atof(words[5]),
		ft_atof(words[6]), ft_atof(words[7]));
	s->at_light++;
}
