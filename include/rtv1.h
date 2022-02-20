/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:30:59 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:53:44 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <stdlib.h> // malloc
# include <math.h> // math
# include <fcntl.h> // open/close
//SDL
# include "../libSDL2/include/SDL2/SDL.h"
//libft
# include "../libft/includes/libft.h"
//defs
# include "defines.h"

//typedef t_bool (*t_get)(t_ray, struct s_obj, t_point*);

typedef struct s_matrix
{
	double	m[4][4];
}			t_matrix;

typedef struct s_pixel
{
	uint32_t	x;
	uint32_t	y;
}				t_pixel;

typedef struct s_vec4
{
	double	x;
	double	y;
	double	z;
	double	w;
}			t_vec4;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_flags
{
	int	cam;
	int	objs;
	int	lights;
}		t_flags;

typedef struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	sqroot;
}			t_quadratic;

typedef struct s_colour
{
	double		r;
	double		g;
	double		b;
	double		a;
}				t_colour;

typedef struct s_buffer
{
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_buffer;

typedef struct s_ray
{
	t_vec	start;
	t_vec	end;
	t_vec	dir;
	double	t;
}			t_ray;

typedef struct s_channels
{
	double		*r;
	double		*g;
	double		*b;
	uint32_t	w;
	uint32_t	h;
}				t_channels;

typedef struct s_point
{
	t_vec		poi;
	t_vec		normal;
	t_colour	colour;
	double		intensity;
}			t_point;

typedef struct s_obj
{
	t_colour	colour;
	t_matrix	tform;
	t_matrix	inv;
	t_vec		trans;
	t_vec		rot;
	t_vec		scale;
	int			shape;
	t_bool		((*get_t)(t_ray, struct s_obj, t_point *));
}				t_obj;

typedef struct s_light
{
	t_vec		pos;
	t_colour	colour;
	double		intensity;
}				t_light;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	look_at;
	t_vec	up;
	t_vec	u;
	t_vec	v;
	t_vec	centre;
	t_vec	alignment;
	double	length;
	double	horizon;
	double	aspect_ratio;
}				t_camera;

typedef struct s_scene
{
	int			objcount;
	t_obj		*objs;
	int			at_obj;
	int			lcount;
	t_light		*lights;
	int			at_light;
	t_camera	camera;
	t_point		closest;
	t_point		current;
	t_colour	max;
	int			raycount;
}				t_scene;

typedef struct s_img
{
	SDL_Renderer	*rend;
	SDL_Window		*win;
	SDL_Texture		*win_tex;
	void			*win_pixels;
	t_buffer		*win_buffer;
	t_channels		*channels;
	int				win_pixel_pitch;
	t_bool			run;
	t_scene			scene;
	double			x_fact;
	double			y_fact;
}					t_img;

//main & initialisation
void		init(t_img *img);
void		init_point(t_point *p);
void		init_colour(t_colour *c);
void		init_camera(t_camera *cam);

//parsing
void		parser(t_scene *scene, char *str);
void		parse_camera(char **words, t_camera *cam, t_flags *flags);
void		parse_light(char **words, t_scene *s, t_flags *flags);
void		parse_object(char **words, t_scene *s, t_flags *flags);

//functions
void		e_keys(SDL_Event e, t_img *img);
void		e_mouse(SDL_Event e, t_img *img);

//camera
void		init_camera(t_camera *cam);
void		camera_update(t_camera *cam);

//drawing & rendering
void		render(t_img *img);
void		draw_pixel(uint32_t x, uint32_t y, t_buffer *buf, uint32_t color);
void		draw_image(t_img *img, t_channels *c);
void		draw_img_to_window(t_img *img);

//rays
t_ray		ray_gen(t_vec start, t_vec end);
t_ray		ray_gen_cam(t_img *img, int x, int y);
void		ray_copy(t_ray *from, t_ray *to);

//sphere
t_bool		sphere_t(t_ray ray, t_obj obj, t_point *p);
double		get_intersect(t_ray *ray);

//plane
t_bool		plane_t(t_ray ray, t_obj obj, t_point *p);
void		plane_test(t_obj *plane);

//cylinder & cone
t_bool		cylinder_t(t_ray ray, t_obj obj, t_point *p);
t_bool		cone_t(t_ray ray, t_obj obj, t_point *p);
t_bool		cc_area_intersect(t_obj obj, t_point *p);
t_bool		cc_base_intersect(t_obj obj, t_point *p);
void		cc_calc_t(t_quadratic q, double *t, t_vec v, t_ray ray);
void		cc_calc_poi(t_vec *poi, double *t, t_vec v, t_ray ray);

//vector
void		init_vec(t_vec *v);
void		vec_copy(t_vec *from, t_vec *to);
void		vec_set(t_vec *v, double x, double y, double z);

//vector math
double		vec_magn(t_vec v);
void		vec_normalise(t_vec *v);
t_vec		vec_cross(t_vec a, t_vec b);
double		vec_dot(t_vec a, t_vec b);
t_vec		vec_scale(t_vec a, double scale);
t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_sub(t_vec a, t_vec b);

//matrices
t_matrix	m_make_identity(void);
void		m_set_identity(t_matrix *m);
void		m_set_value(t_matrix *m, int row, int column, double value);
void		m_print(t_matrix m);
t_matrix	m_inverse(t_matrix m);
t_matrix	m_multiply(t_matrix ma, t_matrix mb);
void		m_transform(t_matrix *m, t_vec trans, t_vec rot, t_vec scale);
void		m_apply_vec(t_vec *vec, t_matrix m);
void		m_apply_ray(t_ray *ray, t_obj obj, t_bool flag);
t_vec4		m_multiply_vec(t_matrix m, t_vec4 v);
void		m_rotate_x(t_matrix *m, t_vec rot);
void		m_rotate_y(t_matrix *m, t_vec rot);
void		m_rotate_z(t_matrix *m, t_vec rot);
void		m_invert_arr(double *m);
t_matrix	m_arr_to_m(double *arr);
void		m_m_to_arr(t_matrix m, double *arr);

//lights
void		init_light(t_light *light);
double		light_check_illum(t_scene *s, int currentObj,
				t_light *light, t_point *p);
t_bool		light_check(t_scene *s, t_point *closest, int obj);
void		print_light(t_light *l);

//colours
int			ft_colour(int r, int g, int b);
void		colour_fset(t_colour *c, double r, double g, double b);
void		colour_check_max(t_colour *max, t_colour c);
void		colour_fset_clamp(t_colour *c, double r, double g, double b);

//materials
t_bool		compute_colour(t_scene *s, t_point *closest, t_ray ray, int obj);

//utils
void		print_vec(t_vec v);
void		print_vec_nl(t_vec v);
void		print_pixel(t_pixel p);
void		print_obj(t_obj obj);
void		print_colour(t_colour c);
t_bool		close_enough(double a, double b);
double		d_to_rad(int deg);

#endif
