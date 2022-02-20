/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:00 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:01 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Handles key events for the mapmaker.
*/
void	e_keys(SDL_Event e, t_img *img)
{
	int	key;

	key = e.key.keysym.sym;
	if (key == SDLK_ESCAPE)
		img->run = FALSE;
}
