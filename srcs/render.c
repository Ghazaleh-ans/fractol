/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:37 by gansari           #+#    #+#             */
/*   Updated: 2025/03/04 15:00:39 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (ft_strcmp(fract->name, JULIA) == 0)
		iter = compute_julia(fract, c, x, y);
	else
	{
		c->im = (y / fract->zoom) + fract->offset_y;
		if (ft_strcmp(fract->name, MANDELBROT) == 0)
			iter = compute_mandelbrot(fract, c);
		else if (ft_strcmp(fract->name, BURNINGSHIP) == 0)
			iter = compute_burning_ship(fract, c);
		else if (ft_strcmp(fract->name, TRICORN) == 0)
			iter = compute_tricorn(fract, c);
	}
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
	if (ft_strcmp(fractal->name, JULIA) == 0)
	{
		c.re = fractal->julia_x;
		c.im = fractal->julia_y;
	}
	while (x < WIN_SIZE)
	{
		if (ft_strcmp(fractal->name, JULIA) != 0)
			c.re = (x / fractal->zoom) + fractal->offset_x;
		process_row(fractal, &c, x);
		x++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window, \
							fractal->image.img, 0, 0);
}
