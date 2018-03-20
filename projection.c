/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 14:50:27 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/20 15:11:29 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ANGLE_X holder->angle_x

void	ft_projection_iso(t_points *map, t_points *copy_map, t_mlx *holder)
{
	t_points	*head;
	t_points	*copy_head;
	double		x;
	double		y;
	double		z;

	head = map;
	copy_head = copy_map;
	while (map->next)
	{
		x = copy_map->x;
		y = copy_map->y;
		z = copy_map->z;
		map->x = x * cos(holder->angle * RAD) - y * sin(holder->angle * RAD);
		map->y = x * sin(holder->angle * RAD) + y * \
			cos(holder->angle * RAD);
		y = map->y;
		map->y = y * cos(ANGLE_X * RAD) - z * sin(holder->angle_x * RAD);
		map->z = -y * sin(ANGLE_X * RAD) - z * cos(holder->angle_x * RAD);
		map->y = map->y + map->z;
		map = map->next;
		copy_map = copy_map->next;
	}
	copy_map = copy_head;
	map = head;
}

void	ft_projection_other(t_points *map)
{
	t_points	*head;
	float		px;
	float		py;
	int			u;
	int			v;

	head = map;
	while (map->next)
	{
		px = (map->z != 0) ? map->x / map->z : map->x;
		py = (map->z) ? map->y / map->z : map->y;
		u = (map->x * 0.81418) - (map->y * 0.3257);
		v = (map->x * 0.5806) + (map->y * 0.9454);
		map->x = (int)px;
		map->y = (int)py - map->z;
		map = map->next;
	}
	map = head;
}

void	ft_projection_default(t_points *map, t_points *copy_map, t_mlx *holder)
{
	t_points	*head;
	t_points	*copy_head;
	double		x;
	double		y;
	double		z;

	head = map;
	copy_head = copy_map;
	while (map->next)
	{
		x = copy_map->x;
		y = copy_map->y;
		z = copy_map->z;
		map->x = x * cos(holder->angle * RAD) - y * sin(holder->angle * RAD);
		map->y = x * sin(holder->angle * RAD) + y * \
			cos(holder->angle * RAD) - copy_map->z;
		map = map->next;
		copy_map = copy_map->next;
	}
	copy_map = copy_head;
	map = head;
}
