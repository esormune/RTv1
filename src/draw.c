/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:23:07 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:27:49 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
*	Colors the pixel in given coordinates of the given buffer as the given
*	hexadecimal value [0xAARRGGBB]. (00 for AA being zero transparency)
*/
void	draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color)
{
	uint32_t	i;

	i = (buf->w * y) + x;
	if (x < buf->w && y < buf->h)
		buf->px[i] = color;
}

/*
** Calculates and returns the max value from the image.
*/
static double	calc_max(t_colour max)
{
	double	ret;

	ret = max.r;
	if (ret < max.g)
		ret = max.g;
	if (ret < max.b)
		ret = max.b;
	return (ret);
}

/*
** Converts rgb channel data with a balanced max value into a uint32_t.
*/
uint32_t	convert_colour(double r, double g, double b, double max)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	uint32_t		colour;

	red = (unsigned char)((r / max) * 255.0);
	green = (unsigned char)((g / max) * 255.0);
	blue = (unsigned char)((b / max) * 255.0);
	colour = ft_colour(red, green, blue);
	return (colour);
}

/*
** Gets max value from the rgb channels, then loops through all the
** pixels and gets the channel values, converting the colours
** a uint32_t, saving that onto the window buffer.
*/
void	draw_image(t_img *img, t_channels *c)
{
	double	max_colour;
	int		x;
	int		y;
	int		at;

	y = 0;
	max_colour = calc_max(img->scene.max);
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			at = c->w * y + x;
			draw_pixel(x, y, img->win_buffer, \
				convert_colour(c->r[at], c->g[at], c->b[at], max_colour));
			x++;
		}
		y++;
	}
}

/*
** Copies drawn image buffer into the pixels to be displayed by
** the SDL library.
*/
void	draw_img_to_window(t_img *img)
{
	if (SDL_LockTexture(img->win_tex, NULL, \
		&img->win_pixels, &img->win_pixel_pitch) < 0)
		ft_getout(SDL_GetError());
	ft_memcpy(img->win_pixels, img->win_buffer->px, \
			WIN_H * img->win_pixel_pitch);
	SDL_UnlockTexture(img->win_tex);
	if (SDL_RenderCopy(img->rend, img->win_tex, NULL, NULL) < 0)
		ft_getout(SDL_GetError());
	SDL_RenderPresent(img->rend);
}
