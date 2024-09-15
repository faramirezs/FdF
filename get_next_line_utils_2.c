/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:43:14 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 16:44:31 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

char	*extract_line(char *big_buffer)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!big_buffer[i])
		return (NULL);
	while (big_buffer[i] != '\n' && big_buffer[i])
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (big_buffer[i] && big_buffer[i] != '\n')
	{
		line[i] = big_buffer[i];
		i++;
	}
	if (big_buffer[i] == '\n')
	{
		line[i] = big_buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*obtain_remaining(char *big_buffer)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (big_buffer[i] != '\0' && big_buffer[i] != '\n')
		i++;
	if (big_buffer[i] == '\0')
	{
		return (NULL);
	}
	tmp = (char *)ft_calloc(ft_strlen(big_buffer) - i + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (big_buffer[i] != '\0')
		tmp[j++] = big_buffer[i++];
	tmp[j] = '\0';
	return (tmp);
}
