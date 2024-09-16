/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:35:46 by alramire          #+#    #+#             */
/*   Updated: 2024/09/16 16:50:48 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	check_file_name(char *filename)
{
	int	i;

	i = 0;
	while (*(filename + i) != '.' && *(filename + i) != '\0')
		i++;
	if (i == 0 || ft_strncmp(filename + i, ".fdf", 4))
	{
		exit(1);
	}
	if (*(filename + i + 4))
	{
		exit(1);
	}
}

static int	validate_line_width(int fd, int width)
{
	char	*line;
	int		current_width;

	line = get_next_line(fd, 0);
	while (line)
	{
		current_width = get_width(line);
		if (width != current_width)
		{
			free(line);
			close(fd);
			get_next_line(-1, 1);
			return (0);
			line = get_next_line(fd, 0);
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	return (1);
}

void	check_width(t_fdf *fdf, char *filename)
{
	char	*line;
	int		fd;
	int		width;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit(1);
	line = get_next_line(fd, 0);
	if (!line)
	{
		close(fd);
		exit(1);
	}
	width = get_width(line);
	free(line);
	if (!validate_line_width(fd, width))
		exit(1);
	fdf->width = width;
	close(fd);
}
