/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:31 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:31 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Sets an x rotation matrix.
*/
void	m_rotate_x(t_matrix *m, t_vec rot)
{
	m_set_identity(m);
	m->m[1][1] = cos(rot.x);
	m->m[1][2] = -sin(rot.x);
	m->m[2][1] = sin(rot.x);
	m->m[2][2] = cos(rot.x);
}

/*
** Sets a y rotation matrix.
*/
void	m_rotate_y(t_matrix *m, t_vec rot)
{
	m_set_identity(m);
	m->m[0][0] = cos(rot.y);
	m->m[0][2] = sin(rot.y);
	m->m[2][0] = -sin(rot.y);
	m->m[2][2] = cos(rot.y);
}

/*
** Sets a z rotation matrix.
*/
void	m_rotate_z(t_matrix *m, t_vec rot)
{
	m_set_identity(m);
	m->m[0][0] = cos(rot.z);
	m->m[0][1] = -sin(rot.z);
	m->m[1][0] = sin(rot.z);
	m->m[1][1] = cos(rot.z);
}
