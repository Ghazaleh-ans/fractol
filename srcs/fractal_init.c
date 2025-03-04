#include "fractol.h"

void	reset_fractal(t_fractal *fractal, char *fractal_name)
{
	fractal->name = fractal_name;
	fractal->zoom = WIN_SIZE / 4;
	fractal->offset_x = -2;
	fractal->offset_y = -2;
	fractal->color = DEFAULT_COLOR;
	fractal->iterations = MIN_ITERATIONS;
}

void	set_fractal(t_fractal *fractal, char *name)
{
	if (!fractal || !name)
		return ;
	if (ft_strcmp(name, MANDELBROT) == 0)
		fractal->name = MANDELBROT;
	else if (ft_strcmp(name, JULIA) == 0)
		fractal->name = JULIA;
	else if (ft_strcmp(name, BURNINGSHIP) == 0)
		fractal->name = BURNINGSHIP;
	else if (ft_strcmp(name, TRICORN) == 0)
		fractal->name = TRICORN;
	else
		wrong_input();
}

void	init_fractal(t_fractal *fractal, char *name)
{
	int	pixel_bits;
	int	line_length;
	int	endian;

	if (!fractal || !name)
		return ;
	reset_fractal(fractal, MANDELBROT);
	set_fractal(fractal, name);
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		error_message("ERROR : mlx_init\n");
	fractal->window = mlx_new_window(fractal->mlx, WIN_SIZE, WIN_SIZE, \
												fractal->name);
	fractal->image.img = mlx_new_image(fractal->mlx, WIN_SIZE, WIN_SIZE);
	if (!fractal->window || !fractal->image.img)
	{
		mlx_destroy_image(fractal->mlx, fractal->image.img);
		mlx_destroy_window(fractal->mlx, fractal->window);
		error_message("ERROR : window and image creation\n");
	}
	fractal->image.addr = mlx_get_data_addr(fractal->image.img ,\
								&pixel_bits, &line_length, &endian);
	fractal->image.bits_per_pixel = pixel_bits;
	fractal->image.line_length = line_length;
	fractal->image.endian = endian;
}
