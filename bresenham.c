/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:40 by alramire          #+#    #+#             */
/*   Updated: 2024/09/11 19:47:00 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/fdf.h"

void draw_line(t_img *img, t_map *start, t_map *end)
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
