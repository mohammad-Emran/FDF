/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <malja-fa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:19:56 by malja-fa          #+#    #+#             */
/*   Updated: 2025/01/03 12:04:04 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		pixel = data->addr + (y * data->line_length + x * (data->bits_per_pixel
					/ 8));
		*(unsigned int *)pixel = color;
	}
}

int	is_valid_char(char c, int base)
{
	if (c >= '0' && c <= '9')
		return (c - '0' < base);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10 < base);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10 < base);
	return (0);
}

int	char_to_value(char c)
{
	int	value;

	value = 0;
	if (c >= '0' && c <= '9')
		value = c - '0';
	if (c >= 'A' && c <= 'F')
		value = c - 'A' + 10;
	if (c >= 'a' && c <= 'f')
		value = c - 'a' + 10;
	return (value);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	value;
	int	i;

	if (base < 2 || base > 16)
		return (0);
	result = 0;
	sign = 1;
	i = 0;
	if (base == 16 && str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	if (str[i] == '-' && base == 10)
	{
		sign = -1;
		i++;
	}
	while (str[i] && is_valid_char(str[i], base))
	{
		value = char_to_value(str[i]);
		result = result * base + value;
		i++;
	}
	return (result * sign);
}
