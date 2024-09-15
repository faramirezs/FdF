/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:13:40 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 15:31:32 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	ft_delta(t_bresenh *delta, t_map *start, t_map *end)
{
	delta->x0 = round(start->x2d);
	delta->y0 = round(start->y2d);
	delta->x1 = round(end->x2d);
	delta->y1 = round(end->y2d);
	delta->dx = abs(delta->x1 - delta->x0);
	delta->dy = -abs(delta->y1 - delta->y0);
	if (delta->x0 < delta->x1)
		delta->sx = 1;
	else
		delta->sx = -1;
	if (delta->y0 < delta->y1)
		delta->sy = 1;
	else
		delta->sy = -1;
	delta->err = delta->dx + delta->dy;
}

void	draw_line(t_img *img, t_map *start, t_map *end, t_fdf *fdf)
{
	t_bresenh	delta;
	int			e2;

	ft_delta(&delta, start, end);
	while (1)
	{
		if (delta.x0 >= fdf->x2d_min && delta.x0 <= fdf->x2d_max
			&& delta.y0 >= fdf->y2d_min && delta.y0 <= fdf->y2d_max)
			img_pix_put(img, delta.x0, delta.y0, start->color);
		if (delta.x0 == delta.x1 && delta.y0 == delta.y1)
			break ;
		e2 = 2 * delta.err;
		if (e2 >= delta.dy)
		{
			delta.err += delta.dy;
			delta.x0 += delta.sx;
		}
		if (e2 <= delta.dx)
		{
			delta.err += delta.dx;
			delta.y0 += delta.sy;
		}
	}
}

void	draw_map(t_fdf *fdf)
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
			if (i < fdf->width - 1)
				draw_line(&fdf->img, point, (*(fdf->map + j) + (i + 1)), fdf);
			if (j < fdf->height - 1)
				draw_line(&fdf->img, point, (*(fdf->map + (j + 1)) + i), fdf);
			i++;
		}
		j++;
	}
}
