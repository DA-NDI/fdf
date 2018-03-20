/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:17:39 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/20 15:41:33 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define INIT holder->init

static void	ft_init_image(t_mlx *holder)
{
	holder->img_new = mlx_new_image(INIT, holder->width, holder->height);
	holder->img_addr = mlx_get_data_addr(holder->img_new, &(holder->bpp), \
		&(holder->size_line), &(holder->endian));
}

static void	display_menu(t_mlx *holder)
{
	mlx_string_put(holder->init, holder->window, 5, 0, 2000, "---Hey! I'm  \
Menu -------");
	mlx_string_put(holder->init, holder->window, 5, 30, 3000, "*Up          \
	{u} ********");
	mlx_string_put(holder->init, holder->window, 5, 60, 4000, "**Down       \
	{d} ********");
	mlx_string_put(holder->init, holder->window, 5, 90, 5000, "**Left       \
	{l} ********");
	mlx_string_put(holder->init, holder->window, 5, 120, 25000, "**Right      \
	{r} ********");
	mlx_string_put(holder->init, holder->window, 5, 150, 25000, "**Lifting   \
up arrow ****");
	mlx_string_put(holder->init, holder->window, 5, 180, 25000, "**Descent   \
down arrow **");
	mlx_string_put(holder->init, holder->window, 5, 210, 25000, "**Rotate z+ \
	{<--} *******");
	mlx_string_put(holder->init, holder->window, 5, 240, 25000, "**Rotate z- \
	{-->} *******");
	mlx_string_put(holder->init, holder->window, 5, 270, 25000, "**Rotate x+  \
	{x}  *******");
	mlx_string_put(holder->init, holder->window, 5, 300, 25000, "**Rotate x-  \
	{`}  *******");
	mlx_string_put(holder->init, holder->window, 5, 330, 19, "**Zoom + - \
	{=, -}  ******");
}

static void	to_bresen(t_points *map, t_mlx *holder)
{
	t_points *head;

	head = map;
	while (map->next)
	{
		if (map->down && (map->down->x + holder->width / 2) > 0)
		{
			holder->x1 = map->x + holder->width / 2;
			holder->x2 = map->down->x + holder->width / 2;
			ft_put_line((int)map->y + holder->height / 2, \
				(int)(map->down->y + holder->height / 2), holder, map);
		}
		if (map->previous && !map->first && \
			(map->previous->x + holder->width / 2) > 0)
		{
			holder->x1 = map->previous->x + holder->width / 2;
			holder->x2 = map->x + holder->width / 2;
			ft_put_line((int)map->previous->y + holder->height / 2, \
				(int)(map->y + holder->height / 2), holder, map);
		}
		map = map->next;
	}
	map = head;
}

int			draw(t_points *map, t_mlx *holder, int height, int wide)
{
	t_points *head;

	head = map;
	ft_init_image(holder);
	while (map->next)
	{
		map->x = (holder->scale != 1) ? map->x * holder->scale : map->x;
		map->y = (holder->scale != 1) ? map->y * holder->scale : map->y;
		map->z = (holder->scale != 1) ? map->z * holder->scale : map->z;
		map->x = (wide == 1 || wide == -1) ? map->x + wide * 15 : map->x;
		map->y = (height == 1 || height == -1) ? map->y - height * 15 : map->y;
		if (holder->scale == 1 && height == 0 && wide == 0 && !holder->angle_x \
	&& !holder->is_angle_x && (holder->high_low == -1 || holder->high_low == 1))
		{
			map->y = (holder->high_low == -1) ? map->y - map->z / 4 \
			: map->y + map->z / 4;
		}
		map->colour = (holder->is_colour) ? map->colour : get_colour(map);
		map = map->next;
	}
	map = head;
	to_bresen(map, holder);
	mlx_put_image_to_window(INIT, holder->window, holder->img_new, 0, 0);
	display_menu(holder);
	return (1);
}
