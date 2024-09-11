/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boot_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:50:35 by alramire          #+#    #+#             */
/*   Updated: 2024/09/11 16:32:19 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/fdf.h"


void check_file_name(char *filename)
{
	int i;

	i = 0;
	while (*(filename + i) != '.' && *(filename + i) != '\0')
		i++;
	if (i == 0 || ft_strncmp(filename + i, ".fdf", 4))
	{
		printf("Wrong extension\n");
		return;
	}
	if (*(filename + i + 4))
	{
		printf("wrong format\n");
		return;

	}
}
void get_wh(t_fdf *fdf, char * filename)
{
	char * line;
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return;
	}
	fdf->height++;
	fdf->width = get_width(line);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		fdf->height++;
	}
}

int get_width(char *line)
{
	int i;
	char **row;

	i = 0;
	row = ft_split(line, ' ');
	while(*(row + i))
	{
		i++;
	}
	free(row);
	return (i);

}

void boot_fdf(t_fdf *fdf, char *filename)
{
	check_file_name(filename);
	get_wh(fdf, filename);
	read_map(fdf, filename);
	x2dy2d(fdf);
	printf("end of boot_fdf\n");
}
