/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:37:56 by alramire          #+#    #+#             */
/*   Updated: 2024/09/16 16:42:10 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

int	handle_keypress(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
	{
		cleanup(fdf);
		exit(0);
	}
	return (0);
}

int	handle_close(t_fdf *fdf)
{
	cleanup(fdf);
	exit(0);
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
	if (fdf->mlx.win_ptr)
	{
		mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
		fdf->mlx.win_ptr = NULL;
	}
	if (fdf->img.mlx_img)
	{
		mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->img.mlx_img);
		fdf->img.mlx_img = NULL;
	}
	if (fdf->mlx.mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx.mlx_ptr);
		free(fdf->mlx.mlx_ptr);
		fdf->mlx.mlx_ptr = NULL;
	}
	free_map(fdf);
	get_next_line(-1, 1);
}

/* void	cleanup(t_fdf *fdf)
{
	if (fdf->mlx.win_ptr)
	{
		mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
		fdf->mlx.win_ptr = NULL;
	}
	free_map(fdf);
	get_next_line(-1, 1);
	mlx_loop_end(fdf->mlx.mlx_ptr);
	mlx_destroy_display(fdf->mlx.mlx_ptr);
	free(fdf->mlx.mlx_ptr);
} */

/* 	void	cleanup(t_fdf *fdf)
	{
		mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
		fdf->mlx.win_ptr = NULL;
		free_map(fdf);
		get_next_line(-1, 1);
	}
 */

/* void	cleanup(t_fdf *fdf)
{
	if (fdf->mlx.win_ptr)
	{
		mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
		fdf->mlx.win_ptr = NULL;
	}
	free_map(fdf);
	get_next_line(-1, 1);
} */
/* void	cleanup(t_fdf *fdf)
{
	if (fdf->mlx.win_ptr)
	{
		mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
		fdf->mlx.win_ptr = NULL; // Ensure you set it to NULL after destroying
	}
	if (fdf->mlx.mlx_ptr)
	{
		mlx_destroy_display(fdf->mlx.mlx_ptr);
			// Only destroy the display if valid
		free(fdf->mlx.mlx_ptr);
		fdf->mlx.mlx_ptr = NULL;
	}
	free_map(fdf);
	get_next_line(-1, 1); // Assuming this is to clear some buffer or fd
} */
