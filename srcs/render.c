#include "fractol.h"

void	handle_move(int key, t_fractal *fractal)
{
	if (key == KEY_UP)
		fractal->offset_y -= VIEW_CHANGE_SIZE / fractal->zoom;
	else if (key == KEY_DOWN)
		fractal->offset_y += VIEW_CHANGE_SIZE / fractal->zoom;
	else if (key == KEY_LEFT)
		fractal->offset_x -= VIEW_CHANGE_SIZE / fractal->zoom;
	else if (key == KEY_RIGHT)
		fractal->offset_x += VIEW_CHANGE_SIZE / fractal->zoom;
}

int	compute_fractal(t_fractal *fract, t_complex *c, int x, int y)
{
	int	iter;

	iter = 0;
	if (fract->type != JULIA)
		c->im = (y / fract->zoom) + fract->offset_y;
	else if (!fract->is_julia_lock)
		c->im = (fract->mouse_y / fract->zoom) + fract->offset_y;
	if (fract->type == MANDELBROT)
		iter = compute_mandelbrot(fract, c);
	else if (fract->type == JULIA)
		iter = compute_julia(fract, c, x, y);
	return (iter);
}

void	process_row(t_fractal *fract, t_complex *c, int x)
{
	int	y;
	int	iter;

	y = 0;

	while (y < WIN_SIZE)
	{
		iter = compute_fractal(fract, c, x, y);
		set_pixel_color(fract, x, y, (iter * fract->color));
		y++;
	}
}

void	set_pixel_color(t_fractal *fractal, int x, int y, int color)
{
	int	line_length;
	int	bits_per_pixel;
	int	offset;

	if (x < 0 || x >= WIN_SIZE || y < 0 || y >= WIN_SIZE)
		return ;
	line_length = fractal->image.line_length;
	bits_per_pixel = fractal->image.bits_per_pixel;
	offset = (y * line_length) + ((bits_per_pixel / 8) * x);
	*(int *)(fractal->image.addr + offset) = color;
}

void	render_fractal(t_fractal *fractal)
{
	static t_complex	c;
	int					x;

	x = 0;
	mlx_clear_window(fractal->mlx, fractal->window);
	while (x < WIN_SIZE)
	{
		if (fractal->type != JULIA)
			c.re = (x / fractal->zoom) + fractal->offset_x;
		else if (!fractal->is_julia_lock)
			c.re = (fractal->mouse_x / fractal->zoom) + fractal->offset_x;
		process_row(fractal, &c, x);
		x++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window,
							fractal->image.img, 0, 0);
}
