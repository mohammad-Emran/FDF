/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 08:11:53 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/01 12:10:21 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	iso_projection(t_map *point)
{
	int		row;
	int		col;
	t_angle	angle;

	calculate_scale(point, &angle.scale);
	angle.coss = cos(ISO_ANGLE);
	angle.sinn = sin(ISO_ANGLE);
	row = 0;
	while (row < point->height)
	{
		col = 0;
		while (col < point->width)
		{
			angle.x = point->points[row][col].x;
			angle.y = point->points[row][col].y;
			point->points[row][col].x = angle.scale * (angle.x - angle.y)
				* angle.coss;
			point->points[row][col].y = angle.scale * (angle.x + angle.y)
				* angle.sinn - point->points[row][col].z;
			point->points[row][col].x += WINDOW_WIDTH / 3;
			point->points[row][col].y += WINDOW_HEIGHT / 3;
			col++;
		}
		row++;
	}
}

int	allocate_map_points(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return (0);
	while (i < map->height)
	{
		map->points[i] = malloc(sizeof(t_point) * map->width);
		if (!map->points[i])
		{
			j = 0;
			while (j < i)
				free(map->points[j++]);
			free(map->points);
			return (0);
		}
		i++;
	}
	return (1);
}

void	parse_point(t_point *point, char **point_parts, int x, int y)
{
	point->x = x;
	point->y = y;
	if (point_parts && point_parts[0])
		point->z = ft_atoi(point_parts[0]);
	else
		point->z = 0;
	if (point_parts && point_parts[1])
		point->color = ft_atoi_base(point_parts[1], 16);
	else
		point->color = ft_atoi_base("0xFFFF", 16);
}

void	*parse_map(char **str, t_map *map)
{
	int		i;
	int		j;
	char	**ss;
	char	**point_parts;

	if (!map || !str)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		ss = ft_split(str[i], ' ');
		if (!ss)
			return (free_map(map), NULL);
		j = 0;
		while (j < map->width)
		{
			point_parts = ft_split(ss[j], ',');
			parse_point(&map->points[i][j], point_parts, j, i);
			ft_free_split(point_parts);
			j++;
		}
		ft_free_split(ss);
		i++;
	}
	return ((void *)1);
}

void	draw_map(t_map *map, t_vars *vars)
{
	int	row;
	int	col;

	row = 0;
	iso_projection(map);
	while (row < map->height)
	{
		col = 0;
		while (col < map->width)
		{
			if (col < map->width - 1)
				bren_alg(&map->points[row][col], map->points[row][col + 1].x,
					map->points[row][col + 1].y, &vars->img);
			if (row < map->height - 1)
				bren_alg(&map->points[row][col], map->points[row + 1][col].x,
					map->points[row + 1][col].y, &vars->img);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
}
