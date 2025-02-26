#include "fractol.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	reset_fractal(t_fractal *fractal, char *fractal_name, int fractal_type)
{
	fractal->name = fractal_name;
	fractal->type = fractal_type;
	fractal->zoom = WIN_SIZE / 4;
	fractal->mouse_x = 0;
	fractal->mouse_y = 0;
	fractal->offset_x = -2;
	fractal->offset_y = -2;
	fractal->is_julia_lock = false;
	fractal->color = DEFAULT_COLOR;
	fractal->iterations = MIN_ITERATIONS;
}

void	change_fractal(int key, t_fractal *fractal)
{
	reset_fractal(fractal, "mandelbrot", MANDELBROT);
	if (key == KEY_TWO)
	{
		fractal->name = "julia";
		fractal->type = JULIA;
	}
	else if (key == KEY_THREE)
	{
		fractal->name = "mandelbrot";
		fractal->type = MANDELBROT;
	}
}

void	set_fractal(t_fractal *fractal, char *name)
{
	if (!fractal || !name)
		return ;
	fractal->name = name;
	if (ft_strcmp(name, "mandelbrot") == 0)
		fractal->type = MANDELBROT;
	else if (ft_strcmp(name, "julia") == 0)
		fractal->type = JULIA;
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
	reset_fractal(fractal, "mandelbrot", MANDELBROT);
	set_fractal(fractal, name);
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		error_message("ERROR : mlx_init\n");
	fractal->window = mlx_new_window(fractal->mlx, WIN_SIZE, WIN_SIZE, \
												"Fractol");
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
