/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alramire <alramire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:40:30 by alramire          #+#    #+#             */
/*   Updated: 2024/09/16 11:06:04 by alramire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define SCALE_FACTOR 0.9
# define Z_SCALE_FACTOR 0.2
# define RED_PIXEL 0xFF0000
# define BACKGROUND_COLOR 0xFFFFFF

// ERROR messages
# define MLX_ERROR -1

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_mlx		t_mlx;
typedef struct s_fdf		t_fdf;
typedef struct s_map		t_map;
typedef struct s_img		t_img;
typedef struct s_bresenh	t_bresenh;
typedef struct s_fpoint		t_fpoint;

struct						s_mlx
{
	void					*mlx_ptr;
	void					*win_ptr;
	void					*iso_ptr;
	void					*ortho_ptr;
	void					*intro_ptr;
};

struct						s_img
{
	void					*mlx_img;
	char					*addr;
	int						bpp;
	int						line_bytes;
	int						width;
	int						height;
	int						endian;
};

struct						s_fpoint
{
	float					x;
	float					y;
};

struct						s_fdf
{
	t_map					**map;
	int						height;
	int						width;
	t_img					img;
	t_mlx					mlx;
	int						max;
	int						min;
	float					x2d_min;
	float					y2d_min;
	float					x2d_max;
	float					y2d_max;
	bool					pressed;
	t_fpoint				**fpoint;
};

struct						s_map
{
	int						x;
	int						y;
	int						z;
	unsigned int			color;
	float					x2d;
	float					y2d;
};

struct						s_bresenh
{
	int						dx;
	int						sx;
	int						dy;
	int						sy;
	int						x0;
	int						y0;
	int						y1;
	int						x1;
	int						err;
};

//checks
void						check_file_name(char *filename);
void						check_width(t_fdf *fdf, char *filename);

// Get_next_line
size_t						ft_strlen(char const *s);
char						*append_buffer(char *big_buffer, char *b2);
char						*ft_strchr(const char *s, int c);
char						*ft_strdup(const char *s1);
void						*ft_calloc(size_t count, size_t size);
char						*get_next_line(int fd, int free_static);
char						*obtain_remaining(char *big_buffer);
char						*extract_line(char *big_buffer);

// Utils
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
void						*ft_memset(void *s, int c, size_t n);
int							ft_atoi(const char *str);
char						*ft_strchr(const char *s, int c);
int							ft_atoi_base(char *line);

// boot_fdf
void						boot_fdf(t_fdf *fdf, char *filename);
void						check_file_name(char *filename);
int							get_width(char *line);

// split
int							ft_words_chars(char const *s, char d, int word);
char						**ft_writer(char const *s, char **tmp, char c,
								int words);
char						**ft_split(char const *s, char c);

// map
void						fill_map(t_fdf *fdf, char *line, int j);
void						read_map(t_fdf *fdf, char *filename);

// minilibx
int							init_mlx(t_fdf *fdf);
void						img_pix_put(t_img *img, int x, int y, int color);

// isometric
void						isometric(t_map *point);
int							x2dy2d(t_fdf *fdf);
void						center_and_scale(t_fdf *fdf);
void						min_max_2d(t_fdf *fdf);
void						trans_pos_2d(t_fdf *fdf);
void						apply_transformations(t_fdf *fdf, float multiplier,
								float x_offset, float y_offset);

// bresenham

void						draw_line(t_img *img, t_map *start, t_map *end,
								t_fdf *fdf);
void						draw_map(t_fdf *fdf);

// cleanup and close mlx
void						free_split(char **split);
void						cleanup(t_fdf *fdf);
int							handle_keypress(int keysym, t_fdf *fdf);
int							handle_close(t_fdf *fdf);
void						free_map(t_fdf *fdf);

#endif
