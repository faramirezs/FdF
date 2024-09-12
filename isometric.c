/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:48:06 by alramire          #+#    #+#             */
/*   Updated: 2024/09/12 10:38:22 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void isometric(t_map *point)
{
	float theta = M_PI / 6; // 30 degrees in radians
	float x = point->x;
	float y = point->y;
	float z = point->z;

	point->x2d = (x - y) * cos(theta);
	point->y2d = (x + y) * sin(theta) - z;
}
int x2dy2dtesting(t_fdf *fdf)
{
	int i;
	int j;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while(i < fdf->width)
		{
			//img_pix_put(img, (*(fdf->map + j) + i)->x2d, (*(fdf->map + j) + i)->y2d, (*(fdf->map + j) + i)->color);
			printf("x2d: %f, y2d: %f. at row %d, column %d\n", (*(fdf->map + j) + i)->x2d, (*(fdf->map + j) + i)->y2d, j, i);
			//img_pix_put(img, center_scale(((*(fdf->map) + j) + i)->x, fdf), center_scale(((*(fdf->map) + j) + i)->y, fdf), ((*(fdf->map) + j) + i)->color);
			//img_pix_put(img, i, j, ((*(fdf->map) + j) + i)->color);
			i++;
		}
	j++;
	}
	return (0);
}

void min_max_2d(t_fdf *fdf)
{
	int i;
	int j;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while(i < fdf->width)
		{
			if((*(fdf->map + j) + i)->x2d < fdf->x2d_min)
				fdf->x2d_min = (*(fdf->map + j) + i)->x2d;
			if((*(fdf->map + j) + i)->y2d < fdf->y2d_min)
				fdf->y2d_min = (*(fdf->map + j) + i)->y2d;
			if((*(fdf->map + j) + i)->x2d > fdf->x2d_max)
				fdf->x2d_max = (*(fdf->map + j) + i)->x2d;
			if((*(fdf->map + j) + i)->y2d > fdf->y2d_max)
				fdf->y2d_max = (*(fdf->map + j) + i)->y2d;
			i++;
		}
	j++;
	}
}

void trans_pos_2d(t_fdf *fdf)
{
	int i;
	int j;
	//int temp;
	t_map *point;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while(i < fdf->width)
		{
			point = (*(fdf->map + j) + i);
			point->x2d = point->x2d - fdf->x2d_min;
			point->y2d = point->y2d - fdf->y2d_min;
			//printf("TRANSPOS Row: %i, Col %i. x2d: %f, y2d: %f\n", j, i, point->x2d, point->y2d);
			i++;
		}
	j++;
	}
	printf("Row: %i, Col %i. x2d_min: %f, y2d_min: %f\n", j, i, fdf->x2d_min, fdf->y2d_min);
	printf("TRANSPOS DONE\n");
	fdf->x2d_max = fdf->x2d_max - fdf->x2d_max;
	fdf->x2d_min = fdf->x2d_min - fdf->x2d_min;
	fdf->y2d_max = fdf->y2d_max - fdf->y2d_max;
	fdf->y2d_min = fdf->y2d_min - fdf->y2d_min;
	printf("Row: %i, Col %i. x2d_min: %f, y2d_min: %f\n", j, i, fdf->x2d_min, fdf->y2d_min);
	/* temp = fdf->x2d_max;
	fdf->x2d_max = fdf->x2d_min;
	fdf->x2d_min = temp;
	temp = fdf->y2d_max;
	fdf->y2d_max = fdf->y2d_min;
	fdf->y2d_min = temp; */
	//x2dy2dtesting(fdf);
	min_max_2d(fdf);
}
/* void center_and_scale(t_fdf *fdf)
{
	int i, j;
	float scale_factor;
	float x_offset, y_offset;
	t_map *point;

	// Calculate the scale factor
	if ((fdf->x2d_max - fdf->x2d_min) > (fdf->y2d_max - fdf->y2d_min))
		scale_factor = (WINDOW_WIDTH - 20) / (fdf->x2d_max - fdf->x2d_min);
	else
		scale_factor = (WINDOW_HEIGHT - 20) / (fdf->y2d_max - fdf->y2d_min);

	// Calculate the offsets to center the points
	x_offset = (WINDOW_WIDTH - ((fdf->x2d_max - fdf->x2d_min) * scale_factor)) / 2;// - (fdf->x2d_min * scale_factor);
	y_offset = (WINDOW_HEIGHT - ((fdf->y2d_max - fdf->y2d_min) * scale_factor)) / 2;// - (fdf->y2d_min * scale_factor);

	// Apply translation and scaling to each point
	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			point = (*(fdf->map + j) + i);
			point->x2d = (point->x2d - fdf->x2d_min) * scale_factor + x_offset;
			point->y2d = (point->y2d - fdf->y2d_min) * scale_factor + y_offset;
			printf("Row: %i, Col %i. x2d: %f, y2d: %f\n", j, i, point->x2d, point->y2d); // Print x2d and y2d after transformation
			i++;
		}
		j++;
	}
} */

void center_and_scale(t_fdf *fdf)
{
	int i, j;
	float multiplier;
	float x_offset, y_offset;
	t_map *point;

	// Calculate the scale factor
	float x_range = fdf->x2d_max - fdf->x2d_min;
	float y_range = fdf->y2d_max - fdf->y2d_min;
	printf("x_range: %f, y_range: %f\n", x_range, y_range);

	// Choose the smaller scale factor to ensure the points fit within the window
	if (x_range > y_range) {
		multiplier = (WINDOW_WIDTH * SCALE_FACTOR) / x_range;
	} else {
		multiplier = (WINDOW_HEIGHT * SCALE_FACTOR) / y_range;
	}

	// Calculate the offsets to center the points
	x_offset = (WINDOW_WIDTH - (x_range * multiplier)) / 2;
	y_offset = (WINDOW_HEIGHT - (y_range * multiplier)) / 2;

	// Apply translation and scaling to each point
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

int x2dy2d(t_fdf *fdf)
{
	int i;
	int j;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while(i < fdf->width)
		{
			isometric((*(fdf->map + j) + i));
			printf("x2d: %f y2d: %f\n", (*(fdf->map + j) + i)->x2d, (*(fdf->map + j) + i)->y2d);
			i++;
		}
	j++;
	}
	min_max_2d(fdf);
	printf("Row: %i, Col %i. x2d_min: %f, y2d_min: %f\n", j, i, fdf->x2d_min, fdf->y2d_min);
	printf("Row: %i, Col %i. x2d_max: %f, y2d_max: %f\n", j, i, fdf->x2d_max, fdf->y2d_max);
	trans_pos_2d(fdf);
	printf("After trans_pos\n");
	printf("Row: %i, Col %i. x2d_min: %f, y2d_min: %f\n", j, i, fdf->x2d_min, fdf->y2d_min);
	printf("Row: %i, Col %i. x2d_max: %f, y2d_max: %f\n", j, i, fdf->x2d_max, fdf->y2d_max);
	center_and_scale(fdf);
	return (0);
}

