/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:46:20 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 16:45:43 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

char	*allocate_big_buffer(char *big_buffer)
{
	if (!big_buffer)
	{
		big_buffer = ft_calloc(1, sizeof(char));
		if (!big_buffer)
			return (NULL);
	}
	return (big_buffer);
}

char	*allocate_buffer(char *big_buffer)
{
	char	*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		free(big_buffer);
		return (NULL);
	}
	return (buffer);
}

char	*read_and_append(int fd, char *buffer, char *big_buffer)
{
	int	r_bytes;

	r_bytes = 1;
	while (!ft_strchr(big_buffer, '\n') && r_bytes != 0)
	{
		r_bytes = read(fd, buffer, BUFFER_SIZE);
		if (r_bytes == -1)
		{
			free(big_buffer);
			free(buffer);
			return (NULL);
		}
		buffer[r_bytes] = '\0';
		big_buffer = append_buffer(big_buffer, buffer);
		if (!big_buffer)
		{
			free(buffer);
			return (NULL);
		}
	}
	return (big_buffer);
}

char	*read_file(char *big_buffer, int fd)
{
	char	*buffer;

	big_buffer = allocate_big_buffer(big_buffer);
	if (!big_buffer)
		return (NULL);
	buffer = allocate_buffer(big_buffer);
	if (!buffer)
		return (NULL);
	big_buffer = read_and_append(fd, buffer, big_buffer);
	free(buffer);
	return (big_buffer);
}

char	*get_next_line(int fd, int free_static)
{
	static char	*big_buffer;
	char		*temp;
	char		*line;

	if (free_static)
		return (free(big_buffer), big_buffer = NULL, NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(big_buffer), big_buffer = NULL, NULL);
	big_buffer = read_file(big_buffer, fd);
	if (!big_buffer)
		return (NULL);
	line = extract_line(big_buffer);
	temp = obtain_remaining(big_buffer);
	free(big_buffer);
	big_buffer = temp;
	if (!line && !big_buffer)
		return (NULL);
	return (line);
}
