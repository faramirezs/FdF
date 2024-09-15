/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:48:06 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 11:31:43 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	isometric(t_map *point)
{
	float	theta;
	float	x;
	float	y;
	float	z;

	theta = M_PI / 6;
	x = point->x;
	y = point->y;
	z = point->z;
	point->x2d = (x - y) * cos(theta);
	point->y2d = (x + y) * sin(theta) - z;
}

int	x2dy2dtesting(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
			i++;
		j++;
	}
	return (0);
}

void	min_max_2d(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			if ((*(fdf->map + j) + i)->x2d < fdf->x2d_min)
				fdf->x2d_min = (*(fdf->map + j) + i)->x2d;
			if ((*(fdf->map + j) + i)->y2d < fdf->y2d_min)
				fdf->y2d_min = (*(fdf->map + j) + i)->y2d;
			if ((*(fdf->map + j) + i)->x2d > fdf->x2d_max)
				fdf->x2d_max = (*(fdf->map + j) + i)->x2d;
			if ((*(fdf->map + j) + i)->y2d > fdf->y2d_max)
				fdf->y2d_max = (*(fdf->map + j) + i)->y2d;
			i++;
		}
		j++;
	}
}

void	trans_pos_2d(t_fdf *fdf)
{
	int		i;
	int		j;
	t_map	*point;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			point = (*(fdf->map + j) + i);
			point->x2d = point->x2d - fdf->x2d_min;
			point->y2d = point->y2d - fdf->y2d_min;
			i++;
		}
		j++;
	}
	fdf->x2d_max = fdf->x2d_max - fdf->x2d_max;
	fdf->x2d_min = fdf->x2d_min - fdf->x2d_min;
	fdf->y2d_max = fdf->y2d_max - fdf->y2d_max;
	fdf->y2d_min = fdf->y2d_min - fdf->y2d_min;
	min_max_2d(fdf);
}

void	center_and_scale(t_fdf *fdf)
{
	float	multiplier;
	t_map	*point;
	float	x_range;
	float	y_range;

	int i;
	int j;
	float x_offset;
	float y_offset;

	x_range = fdf->x2d_max - fdf->x2d_min;
	y_range = fdf->y2d_max - fdf->y2d_min;
	if (x_range > y_range)
	{
		multiplier = (WINDOW_WIDTH * SCALE_FACTOR) / x_range;
	}
	else
	{
		multiplier = (WINDOW_HEIGHT * SCALE_FACTOR) / y_range;
	}
	x_offset = (WINDOW_WIDTH - (x_range * multiplier)) / 2;
	y_offset = (WINDOW_HEIGHT - (y_range * multiplier)) / 2;
	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			point = (*(fdf->map + j) + i);
			point->x2d = point->x2d * multiplier + x_offset;
			point->y2d = point->y2d * multiplier + y_offset;
			i++;
		}
		j++;
	}
	fdf->x2d_max = fdf->x2d_max * multiplier + x_offset;
	fdf->x2d_min = fdf->x2d_min * multiplier + x_offset;
	fdf->y2d_max = fdf->y2d_max * multiplier + y_offset;
	fdf->y2d_min = fdf->y2d_min * multiplier + y_offset;
}

int	x2dy2d(t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			isometric((*(fdf->map + j) + i));
			i++;
		}
		j++;
	}
	min_max_2d(fdf);
	trans_pos_2d(fdf);
	center_and_scale(fdf);
	return (0);
}
