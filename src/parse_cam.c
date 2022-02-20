/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:48 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:49 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Parses camera information. Camera will have default 0.0 for
** xyz and if the information given from file is invalid, it
** will keep them.
*/
void	parse_camera(char **words, t_camera *cam, t_flags *flags)
{
	int	max;

	flags->cam++;
	if (flags->cam != 1)
		ft_getout("Too many cameras declared.");
	max = ft_get_arr_size(words);
	if (max != CAM_PARAMS && max != CAM_PARAMS_LOOKAT)
		return ;
	cam->pos.x = (double)ft_atof(words[1]);
	cam->pos.y = (double)ft_atof(words[2]);
	cam->pos.z = (double)ft_atof(words[3]);
	if (max == CAM_PARAMS_LOOKAT)
	{
		cam->look_at.x = (double)ft_atof(words[4]);
		cam->look_at.y = (double)ft_atof(words[5]);
		cam->look_at.z = (double)ft_atof(words[6]);
	}
	camera_update(cam);
}
