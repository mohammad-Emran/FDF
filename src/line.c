/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:02:57 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/03 12:27:38 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	init(t_line *line, t_point *point, int x2, int y2)
{
	line->x = point->x;
	line->y = point->y;
	line->dx = abs(x2 - line->x);
	line->dy = abs(y2 - line->y);
	if (line->x < x2)
		line->x_increment = 1;
	else
		line->x_increment = -1;
	if (line->y < y2)
		line->y_increment = 1;
	else
		line->y_increment = -1;
	if (line->dx > line->dy)
		line->p = 2 * line->dy - line->dx;
	else
		line->p = 2 * line->dx - line->dy;
}

void	draw_horizontal(t_line *line, t_data *data, t_point *point)
{
	int	i;

	i = 0;
	while (i <= line->dx)
	{
		put_pixel(data, line->x, line->y, point->color);
		line->x += line->x_increment;
		if (line->p < 0)
			line->p += 2 * line->dy;
		else
		{
			line->y += line->y_increment;
			line->p += 2 * (line->dy - line->dx);
		}
		i++;
	}
}

void	draw_vertical(t_line *line, t_data *data, t_point *point)
{
	int	i;

	i = 0;
	while (i <= line->dy)
	{
		put_pixel(data, line->x, line->y, point->color);
		line->y += line->y_increment;
		if (line->p < 0)
			line->p += 2 * line->dx;
		else
		{
			line->x += line->x_increment;
			line->p += 2 * (line->dx - line->dy);
		}
		i++;
	}
}

void	bren_alg(t_point *var, int x2, int y2, t_data *data)
{
	t_line	line;

	init(&line, var, x2, y2);
	if (line.dx > line.dy)
		draw_horizontal(&line, data, var);
	else
		draw_vertical(&line, data, var);
}
