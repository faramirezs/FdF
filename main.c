# include "include/fdf.h"

int main(int ac, char **av)
{
	t_fdf fdf;
	if (ac != 2)
		return (-1);
	ft_memset(&fdf, 0, sizeof(t_fdf));
	boot_fdf(&fdf, *(av + 1));
	init_mlx(&fdf);
	printf("Width: %i\n", fdf.width);
	printf("Height: %i\n", fdf.height);
	return (0);

	//int fd;
	//fd = open("42.fdf", O_RDONLY);
	//printf("%s\n", get_next_line(fd));

}








//int main(void)
//{
//    void	*mlx_ptr;
//
//    mlx_ptr = mlx_init();
//    mlx_destroy_display(mlx_ptr);
//    free(mlx_ptr);
//}
