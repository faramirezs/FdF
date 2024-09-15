/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:46:04 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 15:32:46 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*append_buffer(char *big_buffer, char *b2)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = (char *)malloc(ft_strlen(big_buffer) + ft_strlen(b2) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (big_buffer[i])
	{
		tmp[i] = big_buffer[i];
		i++;
	}
	j = 0;
	while (b2[j])
	{
		tmp[i] = b2[j];
		i++;
		j++;
	}
	tmp[i] = '\0';
	free(big_buffer);
	return (tmp);
}

char	*ft_strchr(const char *s, int c)
{
	char			char_c;
	unsigned int	i;

	char_c = (char)c;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == char_c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == char_c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = malloc(ft_strlen(s1) + 1);
	if (!tmp)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*tmp;

	i = 0;
	tmp = malloc(size * count);
	if (!tmp)
		return (NULL);
	while (i < size * count)
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}
