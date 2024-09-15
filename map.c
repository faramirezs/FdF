/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:10:28 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 16:25:20 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	read_map(t_fdf *fdf, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	fdf->map = malloc(sizeof(t_map *) * fdf->height);
	if (!fdf->map)
		return ;
	while (i < fdf->height)
	{
		line = get_next_line(fd, 0);
		if (!line)
		{
			close(fd);
			free(fdf->map);
			return ;
		}
		fill_map(fdf, line, i);
		free(line);
		i++;
	}
}

void	fill_map_values(t_fdf *fdf, char **z_values, char **z_colors, int j)
{
	int	i;

	i = 0;
	while (i < fdf->width)
	{
		(*(fdf->map + j) + i)->x = i;
		(*(fdf->map + j) + i)->y = j;
		if (ft_strchr(*(z_values + i), 44))
		{
			z_colors = ft_split(*(z_values + i), ',');
			if (!z_colors)
				return ;
			(*(fdf->map + j) + i)->z = ft_atoi(*(z_colors + 0))
				* Z_SCALE_FACTOR;
			(*(fdf->map + j) + i)->color = ft_atoi_base(*(z_colors + 1));
			free_split(z_colors);
		}
		else
			(*(fdf->map + j) + i)->z = ft_atoi(*(z_values + i))
				* Z_SCALE_FACTOR;
		i++;
	}
}

void	fill_map(t_fdf *fdf, char *line, int j)
{
	char	**z_values;
	char	**z_colors;

	z_colors = NULL;
	z_values = ft_split(line, ' ');
	if (!z_values)
		return ;
	*(fdf->map + j) = malloc(sizeof(t_map) * fdf->width);
	if (!*(fdf->map + j))
	{
		free_split(z_values);
		return ;
	}
	fill_map_values(fdf, z_values, z_colors, j);
	free_split(z_values);
}
