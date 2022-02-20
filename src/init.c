/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:27:56 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:27:57 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Initialises the t_point struct.
*/
void	init_point(t_point *p)
{
	init_vec(&p->poi);
	init_vec(&p->normal);
	init_colour(&p->colour);
	p->intensity = 0.0;
}

/*
** Initialises the scene struct.
*/
static void	init_scene(t_scene *s)
{
	init_point(&s->closest);
	init_point(&s->current);
	init_colour(&s->max);
	s->raycount = 0;
}

/*
** Initialises the img struct.
*/
static void	init_img(t_img *img)
{
	img->run = TRUE;
	img->win_buffer = (t_buffer *)malloc(sizeof(t_buffer));
	if (!img->win_buffer)
		ft_getout("failed to initialize main buffer");
	img->win_buffer->w = WIN_W;
	img->win_buffer->h = WIN_H;
	img->win_buffer->px = ft_calloc(WIN_W * WIN_H, sizeof(uint32_t));
	img->channels = (t_channels *)malloc(sizeof(t_channels));
	if (!img->channels)
		ft_getout("failed to initialize rgb channel buffer");
	img->channels->w = WIN_W;
	img->channels->h = WIN_H;
	img->channels->r = ft_calloc(WIN_W * WIN_H, sizeof(double));
	img->channels->g = ft_calloc(WIN_W * WIN_H, sizeof(double));
	img->channels->b = ft_calloc(WIN_W * WIN_H, sizeof(double));
	if (!img->channels->r || !img->channels->g || !img->channels->b)
		ft_getout("failed to initialise channels");
	img->x_fact = 1.0 / ((double)WIN_W / 2.0);
	img->y_fact = 1.0 / ((double)WIN_H / 2.0);
	init_scene(&img->scene);
}

/*
** Initialises the SDL library and renderer.
*/
void	init(t_img *img)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		ft_getout(SDL_GetError());
	img->win = SDL_CreateWindow(WIN_NAME, SDL_WINDOWPOS_UNDEFINED, \
		SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, 0);
	if (!img->win)
		ft_getout(SDL_GetError());
	img->rend = SDL_CreateRenderer(img->win, -1, \
		SDL_RENDERER_ACCELERATED);
	if (!img->rend)
		ft_getout(SDL_GetError());
	img->win_tex = SDL_CreateTexture(img->rend, \
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H);
	if (!img->win_tex)
		ft_getout(SDL_GetError());
	init_img(img);
}
