/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colour.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 15:22:32 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/20 15:38:50 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_colour_sec(t_points *map)
{
	int		colour;

	colour = 0;
	if (map->y >= 0 && map->y <= 100)
		colour = 0x1D87C4;
	else if (map->y > 100 && map->y <= 200)
		colour = 0xE5CCFF;
	else if (map->y > 200 && map->y <= 300)
		colour = 0xFF99FF;
	else if (map->y > 300 && map->y <= 400)
		colour = 0xB266FF;
	else if (map->y > 400 && map->y <= 500)
		colour = 0x9933FF;
	else if (map->y > 500 && map->y <= 600)
		colour = 0x7F00FF;
	else if (map->y > 600 && map->y <= 700)
		colour = 0x6600CC;
	else if (map->y > 700 && map->y <= 800)
		colour = 0x4C0099;
	else if (map->y > 800 && map->y <= 900)
		colour = 0x330066;
	else if (map->y > 900)
		colour = 0xFFFFFF;
	return (colour);
}

int		get_colour(t_points *map)
{
	int		colour;

	colour = 0;
	if (map->y <= -700)
		colour = 0x003366;
	else if (map->y > -700 && map->y <= -600)
		colour = 0x004C99;
	else if (map->y > -600 && map->y <= -500)
		colour = 0x0066CC;
	else if (map->y > -500 && map->y <= -400)
		colour = 0x0080FF;
	else if (map->y > -400 && map->y <= -300)
		colour = 0x3399FF;
	else if (map->y > -300 && map->y <= -200)
		colour = 0x66B2FF;
	else if (map->y > -200 && map->y <= -100)
		colour = 0x99CCFF;
	else if (map->y > -100 && map->y < 0)
		colour = 0xCCE5FF;
	else
		colour = get_colour_sec(map);
	return (colour);
}
