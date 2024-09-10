/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:48:06 by alramire          #+#    #+#             */
/*   Updated: 2024/09/10 17:54:45 by alramire         ###   ########.fr       */
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
