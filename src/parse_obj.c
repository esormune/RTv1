/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:57 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:58 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Sets an object's get_t function to the correct one.
*/
static void	set_t(t_obj *obj)
{
	if (obj->shape == SPHERE)
		obj->get_t = (void *)&sphere_t;
	else if (obj->shape == PLANE)
		obj->get_t = (void *)&plane_t;
	else if (obj->shape == CYLINDER)
		obj->get_t = (void *)&cylinder_t;
	else if (obj->shape == CONE)
		obj->get_t = (void *)&cone_t;
	else
		ft_getout("Invalid object.");
}

/*
** Sets an object's type. If not a valid string, exits as error.
*/
static void	set_obj_type(char *str, t_scene *s)
{
	if (ft_strcmp(str, "sphere") == 0)
		s->objs[s->at_obj].shape = SPHERE;
	else if (ft_strcmp(str, "plane") == 0)
		s->objs[s->at_obj].shape = PLANE;
	else if (ft_strcmp(str, "cylinder") == 0)
		s->objs[s->at_obj].shape = CYLINDER;
	else if (ft_strcmp(str, "cone") == 0)
		s->objs[s->at_obj].shape = CONE;
	else
		ft_getout("Invalid object given.");
}

/*
** Parses object information.
*/
void	parse_object(char **words, t_scene *s, t_flags *flags)
{
	int	max;

	flags->objs++;
	if (flags->objs > s->objcount)
		ft_getout("Invalid number of objects.");
	max = ft_get_arr_size(words);
	if (s->at_obj >= s->objcount || max != OBJ_PARAMS)
		ft_getout("Invalid object parameters.");
	set_obj_type(words[1], s);
	vec_set(&s->objs[s->at_obj].trans, ft_atof(words[2]),
		ft_atof(words[3]), ft_atof(words[4]));
	vec_set(&s->objs[s->at_obj].rot, d_to_rad(ft_atoi(words[5])),
		d_to_rad(ft_atoi(words[6])), d_to_rad(ft_atoi(words[7])));
	vec_set(&s->objs[s->at_obj].scale, ft_atof(words[8]),
		ft_atof(words[9]), ft_atof(words[10]));
	if (s->objs[s->at_obj].scale.x <= 0 || s->objs[s->at_obj].scale.y <= 0
		|| s->objs[s->at_obj].scale.z <= 0)
		ft_getout("Invalid object size.");
	colour_fset_clamp(&s->objs[s->at_obj].colour, ft_atof(words[11]),
		ft_atof(words[12]), ft_atof(words[13]));
	m_transform(&s->objs[s->at_obj].tform, s->objs[s->at_obj].trans,
		s->objs[s->at_obj].rot, s->objs[s->at_obj].scale);
	s->objs[s->at_obj].inv = m_inverse(s->objs[s->at_obj].tform);
	set_t(&s->objs[s->at_obj]);
	s->at_obj++;
}
