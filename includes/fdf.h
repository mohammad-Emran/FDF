/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:28:52 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/03 12:18:40 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../ft_printf/includes/ft_printf.h"
# include "../getNextLine/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <X11/ap_keysym.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define ISO_ANGLE 0.5235987756

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_angle
{
	float	sinn;
	float	coss;
	int		x;
	int		y;
	int		z;
	float	scale;
}			t_angle;

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	int		color;
}			t_point;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}			t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	img;
}			t_vars;

typedef struct s_scale
{
	float	min_x;
	float	min_y;
	float	max_x;
	float	max_y;
	float	scale_x;
	float	scale_y;
	float	proj_x;
	float	proj_y;
}			t_scale;

typedef struct s_line
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	p;
	int	x_increment;
	int	y_increment;
	
}		t_line;

char	**map(int fd);
void	bren_alg(t_point *var, int x2, int y2, t_data *data);
void	ft_free_split(char **str);
char	**check_file(char **argv, int argc);
char	*init_window(t_vars *vars);
void	free_map(t_map *map);
void	count_map_dimensions(char **values, t_map *map);
void	iso_projection(t_map *point);
int		allocate_map_points(t_map *map);
void	*parse_map(char **str, t_map *map);
void	draw_map(t_map *map, t_vars *vars);
void	calculate_scale(t_map *map, float *scale);
int		ft_atoi_base(const char *str, int str_base);
int		count_dimension(char **str);
void	put_pixel(t_data *data, int x, int y, int color);

#endif
