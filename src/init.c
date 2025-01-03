/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 08:39:16 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/03 11:30:50 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	error(t_vars *vars, int flag)
{
	if (flag == 1)
		mlx_destroy_display(vars->mlx);
	else if (flag == 2)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
	}
	else if (flag == 3)
	{
		mlx_destroy_image(vars->mlx, vars->img.img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
	}
	free(vars->mlx);
}

char	*init_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (NULL);
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (!vars->win)
	{
		error(vars, 1);
		return (NULL);
	}
	vars->img.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!vars->img.img)
	{
		error(vars, 2);
		return (NULL);
	}
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bits_per_pixel,
			&vars->img.line_length, &vars->img.endian);
	if (!vars->img.addr)
	{
		error(vars, 3);
		return (NULL);
	}
	return ("Done");
}

void	count_map_dimensions(char **values, t_map *map)
{
	char	**columns;
	int		i;

	map->height = 0;
	while (values[map->height])
		map->height++;
	if (map->height > 0)
	{
		columns = ft_split(values[0], ' ');
		i = 0;
		while (columns[i])
			i++;
		map->width = i;
		ft_free_split(columns);
	}
	else
		map->width = 0;
}

void	update_value(t_scale *values, t_point point)
{
	values->proj_x = point.x - point.y;
	values->proj_y = point.x + point.y - point.z;
	values->min_x = fmin(values->min_x, values->proj_x);
	values->max_x = fmax(values->max_x, values->proj_x);
	values->min_y = fmin(values->min_y, values->proj_y);
	values->max_y = fmax(values->max_y, values->proj_y);
}

void	calculate_scale(t_map *map, float *scale)
{
	t_scale	p;
	int		row;
	int		col;
	t_point	point;

	p.min_x = 1000000.0f;
	p.min_y = 1000000.0f;
	p.max_x = -1000000.0f;
	p.max_y = -1000000.0f;
	row = 0;
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			point = map->points[row][col];
			update_value(&p, point);
			col++;
		}
		row++;
	}
	p.scale_x = (float)WINDOW_WIDTH / (p.max_x - p.min_x);
	p.scale_y = (float)WINDOW_HEIGHT / (p.max_y - p.min_y);
	*scale = fmin(p.scale_x, p.scale_y);
}
