/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:20:05 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/03 10:45:50 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	event(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
	{
		if (vars->img.img != NULL)
			mlx_destroy_image(vars->mlx, vars->img.img);
		if (vars->win != NULL)
			mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	return (0);
}

int	close_window(t_vars *vars)
{
	if (vars->img.img != NULL)
		mlx_destroy_image(vars->mlx, vars->img.img);
	if (vars->win != NULL)
		mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

void	hooks(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, event, vars);
	mlx_hook(vars->win, 17, 1L << 17, close_window, vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	map;
	char	**str;

	str = check_file(argv, argc);
	if (!str)
		return (1);
	count_map_dimensions(str, &map);
	if (!allocate_map_points(&map))
	{
		ft_free_split(str);
		return (1);
	}
	parse_map(str, &map);
	ft_free_split(str);
	if (!init_window(&vars))
	{
		free_map(&map);
		return (1);
	}
	draw_map(&map, &vars);
	hooks(&vars);
	free_map(&map);
	mlx_loop(vars.mlx);
	return (0);
}
