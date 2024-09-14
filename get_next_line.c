/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:46:20 by alramire          #+#    #+#             */
/*   Updated: 2024/09/14 17:41:59 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/fdf.h"

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
		free(big_buffer);
		return (NULL);
	}
	tmp = (char *)ft_calloc(ft_strlen(big_buffer) - i + 1, sizeof(char));
	if (!tmp)
	{
		free(big_buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (big_buffer[i] != '\0')
		tmp[j++] = big_buffer[i++];
	tmp[j] = '\0';
	free(big_buffer);
	return (tmp);
}

char	*read_file(char *big_buffer, int fd)
{
	int		r_bytes;
	char	*buffer;

	if (!big_buffer)
		big_buffer = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		return (NULL);
	}
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
	}
	free(buffer);
	return (big_buffer);
}

char	*get_next_line(int fd)
{
	static char	*big_buffer;
	char		*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (big_buffer != NULL)
			free(big_buffer);
		return (NULL);
	}
	big_buffer = read_file(big_buffer, fd);
	if (!big_buffer)
	{
		return (NULL);
	}
	line = extract_line(big_buffer);
	temp = obtain_remaining(big_buffer);
	if (!temp)
	{
		return (NULL);
	}
	big_buffer = ft_strdup(temp);
/* 	if (big_buffer && big_buffer[0] == '\0')
	{
		free(big_buffer);
	} */
	free(temp);
	return (line);
}
