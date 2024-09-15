/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:50:35 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 17:20:01 by alramire         ###   ########.fr       */
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
		printf("Wrong extension\n");
		return ;
	}
	if (*(filename + i + 4))
	{
		printf("wrong format\n");
		return ;
	}
}

void	get_wh(t_fdf *fdf, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd, 0);
	if (!line)
	{
		close(fd);
		return ;
	}
	fdf->height++;
	fdf->width = get_width(line);
	free(line);
	while (true)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		fdf->height++;
		free(line);
	}
}

int	get_width(char *line)
{
	int		i;
	char	**row;

	i = 0;
	row = ft_split(line, ' ');
	while (*(row + i))
	{
		i++;
	}
	i = 0;
	while (row[i])
	{
		free(row[i]);
		i++;
	}
	free(row);
	return (i);
}

void	boot_fdf(t_fdf *fdf, char *filename)
{
	check_file_name(filename);
	get_wh(fdf, filename);
	read_map(fdf, filename);
	x2dy2d(fdf);
}
