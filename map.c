/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:10:28 by alramire          #+#    #+#             */
/*   Updated: 2024/09/14 16:44:31 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void read_map (t_fdf *fdf, char *filename)
{
	int fd;
	char * line;
	int i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return;
	fdf->map = malloc(sizeof(t_map *) * fdf->height);
	if (!fdf->map)
	{
		return;
	}
	while(i < fdf->height)
	{
		line = get_next_line(fd);
		if(!line)
		{
			close(fd);
			free(fdf->map);
			return;
		}
		fill_map(fdf, line, i);
		free(line);
		i++;
	}
}


void fill_map (t_fdf *fdf, char * line, int j)
{
	char **z_values;
	char **z_colors;
	int i;

	i = 0;
	z_values = ft_split(line, ' ');
	if (!z_values)
	{
		return;
	}
	printf("z_values: %s\n", *(z_values + i));
	*(fdf->map + j) = malloc(sizeof(t_map) * fdf->width);
	if (!*(fdf->map + j))
	{
		return;
		free_split(z_values);
	}
	while ( i < fdf->width)
	{
		(*(fdf->map + j) + i)->x = i;
		(*(fdf->map + j) + i)->y = j;
		printf("x:%i y:%i\n", (*(fdf->map + j) + i)->x, (*(fdf->map + j) + i)->y);
		if(ft_strchr(*(z_values + i), 44))
		{
			z_colors = ft_split(*(z_values + i), ',');
			if (!z_colors)
				{
					return;
				}
			(*(fdf->map + j) + i)->z = ft_atoi(*(z_colors + 0)) * Z_SCALE_FACTOR;
			//(*(fdf->map + j) + i)->color = (*(z_colors + 1));
			(*(fdf->map + j) + i)->color = ft_atoi_base(*(z_colors + 1));
			free(z_colors);
		}
		else
			(*(fdf->map + j) + i)->z = ft_atoi(*(z_values + i)) * Z_SCALE_FACTOR;
		if((*(fdf->map + j) + i)->z > fdf->max)
			fdf->max = (*(fdf->map + j) + i)->z;
		if((*(fdf->map + j) + i)->z < fdf->min)
			fdf->min = (*(fdf->map + j) + i)->z;
		printf("x:%i y:%i z:%i color:%i\n", (*(fdf->map + j) + i)->x, (*(fdf->map + j) + i)->y, (*(fdf->map + j) + i)->z, (*(fdf->map + j) + i)->color);
		i++;
	}
	free_split(z_values);
}

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
void free_map(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->height)
	{
		free(fdf->map[i]);
		i++;
	}
	free(fdf->map);
}

void cleanup(t_fdf *fdf)
{
	free_map(fdf);
}
