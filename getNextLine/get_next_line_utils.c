/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malja-fa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:09:19 by malja-fa          #+#    #+#             */
/*   Updated: 2024/09/12 08:09:20 by malja-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	str_len(char *s)
{
	int	length;

	length = 0;
	if (!s)
		return (0);
	while (s[length])
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	char	*help;
	char	temp;

	help = (char *)s;
	temp = (char)c;
	while (*help != '\0')
	{
		if (*help == temp)
			return (help);
		help++;
	}
	if (temp == '\0')
		return (help);
	return (NULL);
}

char	*fill(char *p, char *s1, char *s2)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s1[++i] != '\0')
		p[i] = s1[i];
	while (s2[j] != '\0')
		p[i++] = s2[j++];
	p[i] = '\0';
	ft_free(s1);
	return (p);
}

char	*f_strjoin(char *s1, char *s2)
{
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	p = malloc((str_len(s1) + str_len(s2) + 1) * sizeof(char));
	if (!p)
		return (ft_free(s1));
	return (fill(p, s1, s2));
}
