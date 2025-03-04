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
