/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:19:51 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/03 10:42:47 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	ft_free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
		free(map->points[i++]);
	free(map->points);
}

int	count_points(char *line)
{
	char	**split;
	int		count;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	count = 0;
	while (split[count])
		count++;
	ft_free_split(split);
	return (count);
}

int	count_dimension(char **str)
{
	int	i;
	int	first_count;
	int	current_count;

	first_count = count_points(str[0]);
	if (first_count <= 0)
	{
		write(2, "INVALID MAP\n", 13);
		return (0);
	}
	i = 1;
	while (str[i])
	{
		current_count = count_points(str[i]);
		if (current_count != first_count || current_count <= 0)
		{
			write(2, "INVALID MAP\n", 13);
			return (0);
		}
		i++;
	}
	return (1);
}
