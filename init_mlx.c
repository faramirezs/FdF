/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 10:14:30 by alramire          #+#    #+#             */
/*   Updated: 2024/09/07 14:13:34 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/fdf.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if(x > 0 && x < WINDOW_WIDTH && y > 0 && y < WINDOW_HEIGHT)
	{
		pixel = img->addr + (y * img->width + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}
int center_scale(int coordinate, t_fdf *fdf)
{
	float factor;
	int offset;

	factor = 0;
	offset = 0;
	if (fdf->width > fdf->height)
	{
		factor = WINDOW_WIDTH * SCALE_FACTOR / fdf->width;
		offset = (WINDOW_WIDTH - (fdf->width * factor)) / 2;
	}
	else
	{
		factor = WINDOW_HEIGHT * SCALE_FACTOR / fdf->height;
		offset = (WINDOW_HEIGHT - (fdf->height * factor)) / 2;
	}
	return(coordinate * factor + offset);
}

void	render_background(t_img *img, int color)
{
	int	i = 0;
	int	j = 0;

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

int render_rect(t_img *img, t_fdf *fdf)
{
	int i;
	int j;

	j = 0;
	if(!fdf->mlx.win_ptr)
		return(MLX_ERROR);
	while (j < WINDOW_HEIGHT * 0.5)
	{
		i = 100;
		while(i < WINDOW_WIDTH * 0.5)
		{
			img_pix_put(img, center_scale(((*(fdf->map) + j) + i)->x, fdf), center_scale(((*(fdf->map) + j) + i)->y, fdf), ((*(fdf->map) + j) + i)->color);
			//img_pix_put(img, i, j, ((*(fdf->map) + j) + i)->color);
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
	render_background(&fdf->img, WHITE_PIXEL);
	render_rect(&fdf->img, fdf);


	mlx_put_image_to_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr, fdf->img.mlx_img, 0, 0);

	return (0);
}

int	handle_input(int keysym, t_fdf * fdf)
{
    if (keysym == XK_Escape)
	{
        mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
	}

    printf("Keypress: %d\n", keysym);
    return (0);
}


int	handle_keypress(int keysym, t_fdf * fdf)
{
    if (keysym == XK_Escape)
	{
        mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
		fdf->mlx.win_ptr = NULL;
	}

    printf("Keypress: %d\n", keysym);
    return (0);
}



int init_mlx(t_fdf *fdf)
{
	fdf->mlx.mlx_ptr = mlx_init();
	if (!fdf->mlx.mlx_ptr)
		return (MLX_ERROR);
	fdf->mlx.win_ptr = mlx_new_window(fdf->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if(fdf->mlx.win_ptr == NULL)
	{
		free(fdf->mlx.win_ptr);
		return(MLX_ERROR);
	}
	fdf->img.mlx_img = mlx_new_image(fdf->mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.mlx_img, &fdf->img.bpp,
		&fdf->img.width, &fdf->img.endian);

	mlx_loop_hook(fdf->mlx.mlx_ptr, &render, fdf);
	mlx_hook(fdf->mlx.win_ptr, KeyPress, KeyPressMask, &handle_keypress, fdf);

	mlx_loop(fdf->mlx.mlx_ptr);
	//mlx_destroy_window(fdf->mlx.mlx_ptr, fdf->mlx.win_ptr);
	mlx_destroy_image(fdf->mlx.mlx_ptr,fdf->img.mlx_img);
	mlx_destroy_display(fdf->mlx.mlx_ptr);
	free(fdf->mlx.mlx_ptr);
	return 0;
}
