/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 16:55:52 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 16:57:04 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

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

void	apply_transformations(t_fdf *fdf, float multiplier, float x_offset,
		float y_offset)
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
