#include "fractol.h"

int	on_destroy(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->image.img);
	mlx_destroy_window(fractal->mlx, fractal->window);
	exit(EXIT_SUCCESS);
}

int	on_key_press(int key, t_fractal *fractal)
{
	if (key >= KEY_LEFT && key <= KEY_UP)
		handle_move(key, fractal);
	else if (key == KEY_F && fractal->type == JULIA)
		fractal->is_julia_lock = !(fractal->is_julia_lock);
	else if (key == KEY_ESC)
		on_destroy(fractal);
	render_fractal(fractal);
	return (0);
}

int	on_mouse_scroll(int key, int x, int y, t_fractal *fractal)
{
	if (key == MOUSE_SCRL_UP)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x) - (x / (fractal->zoom / 1.3));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y) - (y / (fractal->zoom / 1.3));
		fractal->zoom /= 1.3;
		if (fractal->iterations > MIN_ITERATIONS)
			--fractal->iterations;
	}
	else if (key == MOUSE_SCRL_DOWN)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x) - (x / (fractal->zoom * 1.3));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y) - (y / (fractal->zoom * 1.3));
		fractal->zoom *= 1.3;
		if (fractal->iterations < MAX_ITERATIONS)
			++fractal->iterations;
	}
	render_fractal(fractal);
	return (0);
}

int	on_mouse_move(int x, int y, t_fractal *fractal)
{
	if (!(fractal->type == JULIA) || fractal->is_julia_lock)
		return (0);
	fractal->mouse_x = x;
	fractal->mouse_y = y;
	render_fractal(fractal);
	return (0);
}
