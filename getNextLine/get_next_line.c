/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:08:58 by malja-fa          #+#    #+#             */
/*   Updated: 2024/09/12 08:09:00 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char *buff)
{
	if (buff)
	{
		free(buff);
		buff = NULL;
	}
	return (NULL);
}

char	*after_line(char *buff)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
		return (ft_free(buff));
	str = malloc((str_len(buff) - i) * sizeof(char));
	if (!str)
		return (ft_free(buff));
	i++;
	while (buff[i])
		str[j++] = buff[i++];
	str[j] = '\0';
	ft_free(buff);
	return (str);
}

char	*trimming(char *buff)
{
	int		i;
	char	*str;

	i = 0;
	if (!buff || !buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (ft_free(buff));
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		str[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*line(char *str, int fd)
{
	char	*buff;
	int		bytes_read;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (ft_free(str));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			ft_free(buff);
			return (ft_free(str));
		}
		buff[bytes_read] = '\0';
		str = f_strjoin(str, buff);
		if (!str)
			return (ft_free (buff));
		if (ft_strchr(str, '\n') || bytes_read == 0)
			break ;
	}
	ft_free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(buff));
	buff = line(buff, fd);
	if (!buff)
		return (NULL);
	str = trimming(buff);
	buff = after_line(buff);
	return (str);
}
/*
int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY| O_CREAT);
	if (fd == -1)
		return (-1);
	while (1)
	{
		str = get_next_line(fd);
			if (str == NULL)
			break ;
		printf("%s",str);
		free (str);
	}
	if(close(fd) < 0)
		return (-1);
	return (0);
}
*/
