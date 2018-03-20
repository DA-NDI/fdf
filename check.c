/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 21:06:45 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/15 15:36:25 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_free_array(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	return (i);
}

int			ft_open_file(char *argv)
{
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("invalid file\n");
		exit(1);
	}
	return (fd);
}

void		ft_print_error(char *str)
{
	ft_printf("%s\n", str);
	exit(1);
}

static void	next_iterations(char *argv, char **line, \
			int fd, t_mlx *holder)
{
	int		i;
	char	*buff;

	i = 0;
	fd = ft_open_file(argv);
	while ((get_next_line(fd, &buff)) > 0)
	{
		holder->line_height++;
		i = 0;
		line = (ft_strsplit(buff, ' '));
		i = ft_free_array(line);
		free(buff);
		if (holder->line_width != i)
			ft_print_error("Invalid map! You don't fool me");
	}
}

int			ft_check_map(char **argv, int fd, t_mlx *holder)
{
	char	*buff;
	char	**line;
	int		i;
	int		check;

	buff = (void*)0;
	i = 0;
	fd = ft_open_file(argv[1]);
	get_next_line(fd, &buff);
	if (!buff || !*buff)
		ft_print_error("Empty map! You don't fool me");
	line = (ft_strsplit(buff, ' '));
	i = ft_free_array(line);
	free(buff);
	check = i;
	holder->line_width = check;
	next_iterations(argv[1], line, i, holder);
	return (check);
}
