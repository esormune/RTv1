/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:10 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:11 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	cleanup(t_img *img)
{
	free(img->win_buffer->px);
	free(img->win_buffer);
	free(img->channels->r);
	free(img->channels->g);
	free(img->channels->b);
	free(img->channels);
	free(img->scene.objs);
	free(img->scene.lights);
	SDL_DestroyTexture(img->win_tex);
	SDL_DestroyRenderer(img->rend);
	SDL_DestroyWindow(img->win);
	SDL_Quit();
}

void	loop(t_img *img)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e))
	{
		if (e.window.event == SDL_WINDOWEVENT_CLOSE)
			img->run = FALSE;
		if (e.window.event == SDL_WINDOWEVENT_EXPOSED)
			draw_img_to_window(img);
		if (e.key.keysym.sym && e.type == SDL_KEYDOWN)
			e_keys(e, img);
	}
	draw_img_to_window(img);
}

int	main(int argc, char **argv)
{
	t_img	img;

	if (argc == 2)
	{
		ft_bzero(&img, sizeof(t_img));
		parser(&img.scene, argv[1]);
		init(&img);
		render(&img);
		while (img.run)
			loop(&img);
		cleanup(&img);
	}
	else
		ft_printf("Usage: ./RTv1 [scene]\n");
	return (0);
}
