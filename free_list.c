/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 05:20:11 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/15 14:15:59 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_list(t_points *map)
{
	t_points	*tmp;

	if (!map)
		return ;
	if (!(map->next))
	{
		free(map);
		return ;
	}
	while (map->next)
	{
		tmp = map;
		map = map->next;
		free(tmp);
	}
	free(map);
}

void	free_all(t_points *map, t_points *copy_map, t_mlx *holder)
{
	free_list(map);
	free_list(copy_map);
	free(holder);
}
