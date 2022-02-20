/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_tform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:35 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:36 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Sets a translation matrix.
*/
void	m_translation(t_matrix *m, t_vec trans)
{
	m_set_identity(m);
	m->m[0][3] = trans.x;
	m->m[1][3] = trans.y;
	m->m[2][3] = trans.z;
}

/*
** Sets a scaling matrix.
*/
void	m_scale(t_matrix *m, t_vec scale)
{
	m_set_identity(m);
	m->m[0][0] = scale.x;
	m->m[1][1] = scale.y;
	m->m[2][2] = scale.z;
}

/*
** Sets translation, rotation, and scaling aspects to a matrix.
*/
void	m_transform(t_matrix *m, t_vec trans, t_vec rot, t_vec scale)
{
	t_matrix	tr;
	t_matrix	sc;
	t_matrix	rx;
	t_matrix	ry;
	t_matrix	rz;

	ft_bzero(m, sizeof(t_matrix));
	m_set_identity(m);
	m_translation(&tr, trans);
	m_scale(&sc, scale);
	m_rotate_x(&rx, rot);
	m_rotate_y(&ry, rot);
	m_rotate_z(&rz, rot);
	*m = m_multiply(tr, rx);
	*m = m_multiply(*m, ry);
	*m = m_multiply(*m, rz);
	*m = m_multiply(*m, sc);
}

/*
** Inverses a 4x4 matrix.
*/
t_matrix	m_inverse(t_matrix m)
{
	t_matrix	out;
	double		*arr;

	arr = ft_calloc(16, sizeof(double));
	if (!arr)
		ft_getout("Malloc failure.");
	m_m_to_arr(m, arr);
	m_invert_arr(arr);
	out = m_arr_to_m(arr);
	free(arr);
	return (out);
}
