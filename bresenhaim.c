/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenhaim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:17:55 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/20 15:08:38 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		draw_with_array1(t_mlx *holder, t_points *map, int i, int y2)
{
	i = holder->x2 * 4 + y2 * holder->size_line;
	if (i < (int)(holder->max) && i > 0 && holder->size_line > (holder->x2 * 4))
	{
		(holder->img_addr)[i] = map->colour;
		(holder->img_addr)[++i] = map->colour >> 8;
		(holder->img_addr)[++i] = map->colour >> 16;
	}
	return (i);
}

static int		draw_with_array2(t_mlx *holder, t_points *map, int i, int y1)
{
	i = holder->x1 * 4 + y1 * holder->size_line;
	if (i < (int)(holder->max) && i > 0 && holder->size_line > (holder->x1 * 4))
	{
		(holder->img_addr)[i] = map->colour;
		(holder->img_addr)[++i] = map->colour >> 8;
		(holder->img_addr)[++i] = map->colour >> 16;
	}
	return (i);
}

static t_bresen	*initialize_variables(int x1, int x2, int y1, int y2)
{
	t_bresen	*extra_var;

	extra_var = (t_bresen*)malloc(sizeof(t_bresen));
	extra_var->deltax = abs(x2 - x1);
	extra_var->deltay = abs(y2 - y1);
	extra_var->signx = x1 < x2 ? 1 : -1;
	extra_var->signy = y1 < y2 ? 1 : -1;
	extra_var->error = extra_var->deltax - extra_var->deltay;
	return (extra_var);
}

void			ft_put_line(int y1, int y2, t_mlx *holder, t_points *map)
{
	int			i;
	int			error2;
	t_bresen	*extra_var;

	extra_var = initialize_variables(holder->x1, holder->x2, y1, y2);
	i = 0;
	i = draw_with_array1(holder, map, i, y2);
	while (holder->x1 != holder->x2 || y1 != y2)
	{
		i = draw_with_array2(holder, map, i, y1);
		error2 = extra_var->error * 2;
		if (error2 > -(extra_var->deltay))
		{
			extra_var->error -= extra_var->deltay;
			holder->x1 += extra_var->signx;
		}
		if (error2 < extra_var->deltax)
		{
			extra_var->error += extra_var->deltax;
			y1 += extra_var->signy;
		}
	}
	free(extra_var);
}
