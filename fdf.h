/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avolgin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 01:13:14 by avolgin           #+#    #+#             */
/*   Updated: 2018/03/20 15:24:35 by avolgin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define PI 3.1415926
# define RAD 0.017453
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include "./libft2.0/ft_printf.h"
# include <stdlib.h>
# include <fcntl.h>

typedef struct		s_mlx
{
	void			*window;
	void			*init;
	void			*image;
	char			*buff;
	int				colour;
	unsigned int	width;
	double			scale;
	int				point_distance;
	unsigned int	height;
	int				map_size;
	float			line_width;
	int				up_down;
	int				left_right;
	int				angle;
	int				angle_x;
	unsigned int	is_angle_x: 1;
	int				high_low;
	unsigned int	is_angle: 1;
	int				x1;
	int				a;
	int				x2;
	int				line_height;
	int				endian;
	void			*img_new;
	int				bpp;
	char			*img_addr;
	int				size_line;
	unsigned int	is_colour: 1;
	double			max;
	struct s_coord	*copy;
}					t_mlx;

typedef struct		s_bresenhaim
{
	int				signx;
	int				signy;
	int				error;
	int				deltax;
	int				deltay;
}					t_bresen;

typedef struct		s_coord
{
	float			x;
	float			y;
	float			z;
	unsigned int	first: 1;
	int				colour;
	struct s_coord	*next;
	t_mlx			*holder;
	struct s_coord	*previous;
	struct s_coord	*up;
	struct s_coord	*down;
}					t_points;

t_points			*ft_read(int fd, t_mlx *holder, t_points *map);
double				ft_fabs(double nbr);
unsigned int		rgb_conv(unsigned char c1, unsigned char c2, \
					unsigned char c3);
void				ft_put_line(int y0, int y1, t_mlx *holder, t_points *map);
int					draw(t_points *map, t_mlx *holder, int height, int wide);
void				redraw(t_points *map, t_mlx *holder, int height, int wide);
t_points			*ft_lst4new();
int					window_redraw(t_mlx *holder);
void				ft_projection_iso(t_points *map, t_points *copy_map, \
					t_mlx *holder);
void				ft_projection_default(t_points *map, t_points *copy_map, \
					t_mlx *holder);
void				ft_projection_other(t_points *map);
t_points			*ft_listcopy(t_points *map);
int					ft_check_map(char **argv, int fd, t_mlx *holder);
void				ft_print_error(char *str);
int					ft_open_file(char *argv);
void				free_list(t_points *map);
void				free_all(t_points *map, t_points *copy_map, t_mlx *holder);
int					get_colour(t_points *map);

#endif
