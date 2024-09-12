/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:40 by alramire          #+#    #+#             */
/*   Updated: 2024/09/12 16:56:57 by alramire         ###   ########.fr       */
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
	int x0 = round(start->x2d);
	int y0 = round(start->y2d);
	int x1 = round(end->x2d);
	int y1 = round(end->y2d);

	int dx = abs(x1 - x0);
	int dy = -abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	while (1) {
		if (x0 >= x2d_min && x0 <= x2d_max && y0 >= y2d_min && y0 <= y2d_max) {
			img_pix_put(img, x0, y0, start->color);
		}

		if (x0 == x1 && y0 == y1) break;

		int e2 = 2 * err;
		if (e2 >= dy) { err += dy; x0 += sx; }
		if (e2 <= dx) { err += dx; y0 += sy; }
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
