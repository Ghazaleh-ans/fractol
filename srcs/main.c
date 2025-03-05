/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:26 by gansari           #+#    #+#             */
/*   Updated: 2025/03/04 15:00:28 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_window(t_fractal *fractal)
{
	fractal->window = mlx_new_window(fractal->mlx, WIN_SIZE, WIN_SIZE, \
						fractal->name);
	if (!fractal->window)
	{
		error_message("Error: Failed to create window\n");
		free(fractal->mlx);
		exit(1);
	}
}

void	init_image(t_fractal *fractal)
{
	fractal->image.img = mlx_new_image(fractal->mlx, WIN_SIZE, WIN_SIZE);
	if (!fractal->image.img)
	{
		mlx_destroy_window(fractal->mlx, fractal->window);
		//mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		error_message("ERROR : Failed to create image\n");
	}
}
void	set_image_address(t_fractal *fractal)
{
	int	pixel_bits;
	int	line_length;
	int	endian;

	fractal->image.addr = mlx_get_data_addr(fractal->image.img, \
							&pixel_bits, &line_length, &endian);
	fractal->image.bits_per_pixel = pixel_bits;
	fractal->image.line_length = line_length;
	fractal->image.endian = endian;
}

void	init_fractal(t_fractal *fractal, char *name)
{

	if (!fractal || !name)
		return ;
	reset_fractal(fractal, MANDELBROT);
	set_fractal(fractal, name);
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		error_message("ERROR : mlx_init\n");
	init_window(fractal);
	init_image(fractal);
	set_image_address(fractal);
}
//mlx_hook(fractal.window, 6, 1L << 6, on_mouse_move, &fractal);
int	main(int argc, char **argv)
{
	t_fractal	fractal;

	check_input(argc, argv, &fractal);
	init_fractal(&fractal, argv[1]);
	render_fractal(&fractal);
	mlx_key_hook(fractal.window, on_key_press, &fractal);
	mlx_mouse_hook(fractal.window, on_mouse_scroll, &fractal);
	mlx_hook(fractal.window, 17, 0, on_destroy, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
