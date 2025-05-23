/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:12 by gansari           #+#    #+#             */
/*   Updated: 2025/03/04 15:00:14 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_color(int key, t_fractal *fractal)
{
	if (key == KEY_Q)
		fractal->color += 0x300000;
	else if (key == KEY_W)
		fractal->color += 0x030000;
	else if (key == KEY_E)
		fractal->color += 0x003000;
	else if (key == KEY_R)
		fractal->color += 0x000300;
	else if (key == KEY_T)
		fractal->color += 0x000030;
	else if (key == KEY_Y)
		fractal->color += 0x000003;
	else if (key == KEY_A)
		fractal->color -= 0x300000;
	else if (key == KEY_S)
		fractal->color -= 0x030000;
	else if (key == KEY_D)
		fractal->color -= 0x003000;
	else if (key == KEY_F)
		fractal->color -= 0x000300;
	else if (key == KEY_G)
		fractal->color -= 0x000030;
	else if (key == KEY_H)
		fractal->color -= 0x000003;
}

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
		help_input();
}
