/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:20:08 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/03 10:49:20 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	check_extention(char *filename)
{
	char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (dot && ft_strncmp(dot + 1, "fdf", 4) == 0)
		return (1);
	write(2, "bad extension of the file\n", 27);
	return (0);
}

char	**del_new_line(char **str)
{
	int	i;
	int	len;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		len = ft_strlen(str[i]);
		if (len > 0 && str[i][len - 1] == '\n')
			str[i][len - 1] = '\0';
		i++;
	}
	return (str);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, new_size / 2);
	free(ptr);
	return (new_ptr);
}

char	**map(int fd)
{
	char	**map;
	int		i;
	int		size;

	size = 1024;
	map = malloc(sizeof(char *) * size);
	if (!map)
		return (NULL);
	i = 0;
	map[i] = get_next_line(fd);
	while (map[i])
	{
		if (i + 1 >= size)
		{
			size *= 2;
			map = ft_realloc(map, sizeof(char *) * size);
			if (!map)
				return (NULL);
		}
		map[++i] = get_next_line(fd);
	}
	map[i] = NULL;
	return (map);
}

char	**check_file(char **argv, int argc)
{
	int		fd;
	char	**str;

	if (argc != 2)
		return (NULL);
	if (!check_extention(argv[1]))
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (NULL);
	str = map(fd);
	close(fd);
	if (!str)
		return (NULL);
	str = del_new_line(str);
	if (!count_dimension(str))
	{
		ft_free_split(str);
		return (NULL);
	}
	return (str);
}
