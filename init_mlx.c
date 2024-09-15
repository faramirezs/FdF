/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:14:30 by alramire          #+#    #+#             */
/*   Updated: 2024/09/15 11:23:55 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
	{
		pixel = img->addr + (y * img->width + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j, i, color);
			j++;
		}
		i++;
	}
}

int	render_rect(t_img *img, t_fdf *fdf)
{
	int	i;
	int	j;

	j = 0;
	if (!fdf->mlx.win_ptr)
		return (MLX_ERROR);
	while (j < fdf->height)
	{
		i = 0;
		while (i < fdf->width)
		{
			img_pix_put(img, (*(fdf->map + j) + i)->x2d, (*(fdf->map + j)
					+ i)->y2d, (*(fdf->map + j) + i)->color);
			i++;
		}
		j++;
	}
	return (0);
}

int	render(t_fdf *fdf)
{
	if (fdf->mlx.win_ptr == NULL)
		return (1);
	render_background(&fdf->img, BACKGROUND_COLOR);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr,
		fdf->img.mlx_img, 0, 0);
	return (0);
}

int	handle_input(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}

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

int	init_mlx(t_fdf *fdf)
{
	fdf->mlx.mlx_ptr = mlx_init();
	if (!fdf->mlx.mlx_ptr)
		return (MLX_ERROR);
	fdf->mlx.win_ptr = mlx_new_window(fdf->mlx.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT, "fdf");
	if (fdf->mlx.win_ptr == NULL)
	{
		free(fdf->mlx.win_ptr);
		return (MLX_ERROR);
	}
	mlx_hook(fdf->mlx.win_ptr, 17, 1L << 17, handle_close, fdf);
	fdf->img.mlx_img = mlx_new_image(fdf->mlx.mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.mlx_img, &fdf->img.bpp,
			&fdf->img.width, &fdf->img.endian);
	mlx_loop_hook(fdf->mlx.mlx_ptr, &render, fdf);
	mlx_hook(fdf->mlx.win_ptr, KeyPress, KeyPressMask, &handle_keypress, fdf);
	mlx_loop(fdf->mlx.mlx_ptr);
	mlx_destroy_image(fdf->mlx.mlx_ptr, fdf->img.mlx_img);
	mlx_destroy_display(fdf->mlx.mlx_ptr);
	free(fdf->mlx.mlx_ptr);
	return (0);
}
