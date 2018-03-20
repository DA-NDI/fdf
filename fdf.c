/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 14:33:41 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/20 16:28:02 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define LEFT_R map->holder->left_right

static t_mlx	*holder_init(char **argv)
{
	t_mlx	*holder;
	int		fd;

	fd = 0;
	fd = ft_open_file(*argv);
	holder = (t_mlx*)malloc(sizeof(t_mlx) * 1);
	holder->colour = 40000;
	holder->height = 1350;
	holder->width = 1800;
	holder->line_height = 1;
	holder->scale = 1;
	holder->line_width = ft_check_map(argv, fd, holder);
	holder->point_distance = (holder->width / (holder->line_width * 1.4)) * 0.7;
	if (!(holder->init = mlx_init()))
		exit(1);
	holder->window = mlx_new_window(holder->init, 1800, 1350, "YO!");
	holder->angle = 45;
	holder->angle_x = 0;
	holder->is_angle_x = 0;
	holder->endian = 0;
	holder->bpp = 8;
	holder->is_colour = 0;
	holder->max = holder->height * holder->width * 4;
	return (holder);
}

static void		reset_flags(t_mlx *holder)
{
	holder->scale = 1;
	holder->high_low = 0;
	holder->is_angle = 0;
	holder->is_angle_x = 0;
	holder->up_down = 0;
	holder->left_right = 0;
}

static void		turn_x(t_points *map, int key)
{
	map->holder->angle += (key == 123) ? 5 : -5;
	ft_projection_iso(map, map->holder->copy, map->holder);
}

static int		deal_key(int key, t_points *map)
{
	reset_flags(map->holder);
	if (key == 53)
		exit(1);
	else if (key == 32 || key == 2)
		map->holder->up_down += (key == 32) ? 1 : -1;
	else if (key == 15 || key == 37)
		map->holder->left_right += (key == 15) ? 1 : -1;
	else if (key == 7 || key == 50)
	{
		map->holder->angle_x += (key == 7) ? 5 : -5;
		ft_projection_iso(map, map->holder->copy, map->holder);
	}
	else if (key == 35)
	{
		map->holder->angle = 45;
		map->holder->angle_x = 0;
		ft_projection_iso(map, map->holder->copy, map->holder);
	}
	else if (key == 123 || key == 124)
		turn_x(map, key);
	else if (key == 126 || key == 125)
		map->holder->high_low = (key == 126) ? 1 : -1;
	else if (key == 24 || key == 27)
		map->holder->scale = (key == 24) ? 1.1 : 0.9;
	return (draw(map, map->holder, map->holder->up_down, LEFT_R));
}

int				main(int argc, char **argv)
{
	t_mlx		*holder;
	t_points	*map;
	t_points	*copy_map;
	int			fd;
	int			i;

	i = 0;
	if (argc != 2)
		ft_print_error("Usage fdf input_file \n");
	map = ft_lst4new();
	copy_map = ft_lst4new();
	holder = holder_init(argv);
	fd = ft_open_file(argv[1]);
	map = ft_read(fd, holder, map);
	fd = ft_open_file(argv[1]);
	copy_map = ft_read(fd, holder, copy_map);
	holder->copy = copy_map;
	map->holder = holder;
	ft_projection_iso(map, holder->copy, holder);
	draw(map, holder, 0, 0);
	mlx_hook(holder->window, 2, 5, deal_key, map);
	mlx_loop(holder->init);
	free_all(map, copy_map, holder);
	return (0);
}
