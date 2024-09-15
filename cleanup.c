/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:37:56 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 15:39:05 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

int	handle_keypress(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
	{
		cleanup(fdf);
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_close(t_fdf *fdf)
{
	cleanup(fdf);
	return (0);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->height)
	{
		free(fdf->map[i]);
		i++;
	}
	free(fdf->map);
}

void	cleanup(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
	fdf->mlx.win_ptr = NULL;
	free_map(fdf);
	get_next_line(-1, 1);
}
