/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 12:43:23 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/20 15:16:13 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define BUF holder->buff
#define A holder->a

static char	*init_variables(float *x, int *y, int *i)
{
	char	*buff;

	*y = 0;
	*i = 0;
	*x = 0;
	buff = (void*)0;
	return (buff);
}

t_points	*ft_lst4new(void)
{
	t_points *newlist;

	if (!(newlist = (t_points*)malloc(sizeof(t_points))))
	{
		ft_printf("Failed to malloc newlist\n");
		exit(1);
	}
	newlist->next = NULL;
	newlist->previous = NULL;
	newlist->up = NULL;
	newlist->down = NULL;
	newlist->x = 0;
	newlist->y = 0;
	newlist->z = 0;
	newlist->colour = (int)0x127EBD;
	newlist->first = 0;
	return (newlist);
}

static int	coma_handle(char *buff, int i, t_points *map, t_mlx *holder)
{
	char	colour[10];

	holder->a = 0;
	while (buff[i] == 32)
		i++;
	if (buff[i] == ',')
	{
		holder->is_colour = 1;
		i = i + 3;
		while (buff[i] != ' ' && buff[i] != '\0')
			colour[A++] = buff[i++];
		colour[A] = '\0';
		map->previous->colour = ft_strtol((char*)colour);
	}
	while (buff[i] == 32)
		i++;
	if (buff[i] == '\0')
		return (-1);
	map->z = buff[i++] - 48;
	while (ft_isdigit(buff[i]))
		map->z = (map->z * 10) + (buff[i++] - 48);
	map->x = (map->x - holder->line_width / 2) * holder->point_distance;
	map->y = map->y * holder->point_distance;
	map->z = map->z * (holder->point_distance) / 3;
	return (i);
}

static void	if_x_if_y(t_points *map, int x, int y, t_points *head)
{
	if (x == 1)
		map->first = 1;
	if (y >= 1)
	{
		head = map;
		map = map->previous;
		while (head->x != map->x)
			map = map->previous;
		head->up = map;
		map->down = head;
		map = head;
	}
	map->next = ft_lst4new();
	map->next->previous = map;
}

t_points	*ft_read(int fd, t_mlx *holder, t_points *map)
{
	int			i;
	float		x;
	int			y;
	t_points	*head_head;

	holder->buff = init_variables(&x, &y, &i);
	holder->copy = map;
	head_head = map;
	while ((get_next_line(fd, (char **)&BUF)) > 0)
	{
		while (BUF[i] != '\0' && !(BUF[i] == 32 && BUF[i + 1] == '\0'))
		{
			map->x = x++;
			map->y = y - holder->line_height / 2;
			if ((i = coma_handle(BUF, i, map, holder)) == -1)
				break ;
			if_x_if_y(map, x, y, holder->copy);
			map = map->next;
		}
		x = 0;
		y++;
		i = 0;
		ft_strdel(&BUF);
	}
	return (head_head);
}
