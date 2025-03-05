/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:59:48 by gansari           #+#    #+#             */
/*   Updated: 2025/03/04 14:59:52 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	on_destroy(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->image.img);
	mlx_destroy_window(fractal->mlx, fractal->window);
	//mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(EXIT_SUCCESS);
}

int	on_key_press(int key, t_fractal *fractal)
{
	if (key >= KEY_LEFT && key <= KEY_DOWN)
		handle_move(key, fractal);
	else if (key == KEY_ESC)
		on_destroy(fractal);
	else if ((key >= KEY_Q && key <= KEY_Y) || (key >= KEY_A && key <= KEY_H))
		change_color(key, fractal);
	else if (key == KEY_PLUS && fractal->iterations < MAX_ITERATIONS)
	{
		fractal->iterations += 16;
		if (fractal->iterations > MAX_ITERATIONS)
			fractal->iterations = MAX_ITERATIONS;
	}
	else if (key == KEY_MINUS && fractal->iterations > MIN_ITERATIONS)
	{
		fractal->iterations -= 16;
		if (fractal->iterations < MIN_ITERATIONS)
			fractal->iterations = MIN_ITERATIONS;
	}
	render_fractal(fractal);
	return (0);
}

int	on_mouse_scroll(int key, int x, int y, t_fractal *fractal)
{
	if (key == MOUSE_SCRL_UP)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x)
			- (x / (fractal->zoom / 1.3));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y)
			- (y / (fractal->zoom / 1.3));
		fractal->zoom /= 1.3;
		// if (fractal->iterations > MIN_ITERATIONS)
		// 	--fractal->iterations;
	}
	else if (key == MOUSE_SCRL_DOWN)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x)
			- (x / (fractal->zoom * 1.3));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y)
			- (y / (fractal->zoom * 1.3));
		fractal->zoom *= 1.3;
		// if (fractal->iterations < MAX_ITERATIONS)
		// 	++fractal->iterations;
	}
	render_fractal(fractal);
	return (0);
}
