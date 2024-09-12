/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:40 by alramire          #+#    #+#             */
/*   Updated: 2024/09/12 09:44:17 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/fdf.h"

/* void draw_line(t_img *img, t_map *start, t_map *end)
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;

	dx = fabsf(end->x2d - start->x2d);
	if(start->x2d < end->x2d)
		sx = 1;
	else
		sx = -1;
	dy = -fabs(end->y2d - start->y2d);
	if(start->y2d < end->y2d)
		sy = 1;
	else
		sy = -1;

	err = dx + dy; // Initialize the error term
	while (1)
	{
		img_pix_put(img, start->x2d, start->y2d, start->color);
		if (start->x2d == end->x2d && start->y2d == end->y2d)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			start->x2d += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			start->y2d += sy;
		}
	}
}

void draw_map(t_fdf *fdf)
{
	int i, j;
	t_map *point;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			point = (*(fdf->map + j) + i);
			if (i < fdf->width - 1)
				draw_line(&fdf->img, point, (*(fdf->map + j) + (i + 1)));
			if (j < fdf->height - 1)
				draw_line(&fdf->img, point, (*(fdf->map + (j + 1)) + i));
			i++;
		}
		j++;
	}
} */


//Testing line from x2d min to max and from y2d from min to max


void draw_line(t_img *img, t_map *start, t_map *end, float x2d_min, float x2d_max, float y2d_min, float y2d_max)
{
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;

	// Check if the line is within the bounds
	printf("Start: (%f, %f), End: (%f, %f), Min: (%f, %f), Max: (%f, %f)\n",
		start->x2d, start->y2d, end->x2d, end->y2d, x2d_min, y2d_max, x2d_max, y2d_max);

	if ((start->x2d < x2d_min && end->x2d < x2d_min) || (start->x2d > x2d_max && end->x2d > x2d_max) ||
		(start->y2d < y2d_min && end->y2d < y2d_min) || (start->y2d > y2d_max && end->y2d > y2d_max))
	{
		printf("Line is out of bounds\n");
		return;
	}
	dx = fabsf(end->x2d - start->x2d);
	if(start->x2d < end->x2d)
		sx = 1;
	else
		sx = -1;
	dy = -fabs(end->y2d - start->y2d);
	if(start->y2d < end->y2d)
		sy = 1;
	else
		sy = -1;

	err = dx + dy; // Initialize the error term
	while (1)
	{
		// Draw the pixel only if it's within the bounds
		if (start->x2d >= x2d_min && start->x2d <= x2d_max && start->y2d >= y2d_min && start->y2d <= y2d_max)
			img_pix_put(img, start->x2d, start->y2d, RED_PIXEL);
		if (start->x2d == end->x2d && start->y2d == end->y2d)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			start->x2d += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			start->y2d += sy;
		}
	}
}

void draw_map(t_fdf *fdf)
{
	int i, j;
	t_map *point;

	j = 0;
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			point = (*(fdf->map + j) + i);
			if (i < fdf->width - 1)
				draw_line(&fdf->img, point, (*(fdf->map + j) + (i + 1)), fdf->x2d_min, fdf->x2d_max, fdf->y2d_min, fdf->y2d_max);
			if (j < fdf->height - 1)
				draw_line(&fdf->img, point, (*(fdf->map + (j + 1)) + i), fdf->x2d_min, fdf->x2d_max, fdf->y2d_min, fdf->y2d_max);
			i++;
		}
		j++;
	}
}
