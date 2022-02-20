/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esormune <esormune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 15:28:39 by esormune          #+#    #+#             */
/*   Updated: 2022/02/18 15:28:40 by esormune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Sets a matrix to default (identity) matrix.
*/
void	m_set_identity(t_matrix *m)
{
	ft_bzero(m, sizeof(t_matrix));
	m->m[0][0] = 1;
	m->m[1][1] = 1;
	m->m[2][2] = 1;
	m->m[3][3] = 1;
}

/*
** Creates and returns an identity matrix.
*/
t_matrix	m_make_identity(void)
{
	t_matrix	m;

	ft_bzero(&m, sizeof(t_matrix));
	m.m[0][0] = 1;
	m.m[1][1] = 1;
	m.m[2][2] = 1;
	m.m[3][3] = 1;
	return (m);
}

/*
** Sets element in matrix.
*/
void	m_set_value(t_matrix *m, int row, int column, double value)
{
	if (column > 4 || column < 0 || row > 4 || row < 0)
		return ;
	m->m[row][column] = value;
}

/*
** Prints a matrix.
*/
void	m_print(t_matrix m)
{
	int	i;
	int	j;

	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			ft_printf("%f ", m.m[j][i]);
			i++;
		}
		ft_printf("\n");
		j++;
	}
}
