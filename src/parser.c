/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:29:01 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:29:01 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Parses given line and saves its data while checking validity.
** For the camera, will take in the most recent. 9 corresponds
** to tabs in the string split.
*/
void	parse_line(char *str, t_scene *scene, t_flags *flags)
{
	char	**words;

	if (str[0] == '#')
		return ;
	words = ft_strsplit(str, 9);
	if (!words)
		ft_getout("Failure in strsplit.");
	if (ft_strcmp(words[0], "camera") == 0)
		parse_camera(words, &scene->camera, flags);
	else if (ft_strcmp(words[0], "object") == 0)
		parse_object(words, scene, flags);
	else if (ft_strcmp(words[0], "light") == 0)
		parse_light(words, scene, flags);
	else
		ft_getout("Invalid file.");
	ft_free_arr(words);
}

/*
** Parses the first lines into obj and lightcount.
*/
int	parse_beginning(int fd, t_scene *scene)
{
	char	*f;
	int		x;
	int		i;

	i = 0;
	x = get_next_line(fd, &(f));
	if (f[0] != '#' || x <= 0)
		ft_getout("Invalid file.");
	free(f);
	x = get_next_line(fd, &(f));
	if (f[0] == '#' || x <= 0)
		ft_getout("Invalid file.");
	scene->objcount = ft_atoi(f);
	if (scene->objcount <= 0 || scene->objcount > 10)
		ft_getout("Bad number of objects.");
	i += ft_numlength(scene->objcount);
	scene->lcount = ft_atoi(&(f[i]));
	if (scene->lcount <= 0 || scene->lcount > 5)
		ft_getout("Bad number of lights.");
	free(f);
	return (0);
}

/*
** Initialises the memory allocation for the scene struct
** after parsing the first line.
*/
static void	init_scene(t_scene *scene)
{
	scene->objs = ft_calloc(scene->objcount, sizeof(t_obj));
	if (!scene->objs)
		ft_getout("Failure to allocate objects.");
	scene->lights = ft_calloc(scene->lcount, sizeof(t_light));
	if (!scene->lights)
		ft_getout("Failure to allocate lights.");
	init_camera(&scene->camera);
	camera_update(&scene->camera);
}

/*
** Loops through the file and saves objects, lights,
** camera points. Any invalid text will invalidate file.
** First row is a comment, second has to have obj count
** & light count.
*/
int	parse_file(int fd, t_scene *scene, t_flags *flags)
{
	char	*f;
	int		x;

	while (1)
	{
		x = get_next_line(fd, &(f));
		if (x == 0)
			break ;
		if (x < 0)
			ft_getout("Open failure.");
		parse_line(f, scene, flags);
		free(f);
	}
	if (flags->objs != scene->objcount || flags->lights != scene->lcount)
		ft_getout("Invalid amount of lights and/or objects.");
	return (0);
}

/*
** Begins parsing the file.
*/
void	parser(t_scene *scene, char *str)
{
	t_flags	flags;
	int		fd;
	int		ret;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		ft_getout("Cannot open file.");
	scene->at_light = 0;
	scene->at_obj = 0;
	ret = parse_beginning(fd, scene);
	if (ret != 0)
		ft_getout("Invalid file.");
	init_scene(scene);
	ft_bzero(&flags, sizeof(t_flags));
	ret = parse_file(fd, scene, &flags);
	if (ret != 0)
		ft_getout("Invalid file.");
}
