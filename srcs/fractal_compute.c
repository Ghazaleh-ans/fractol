/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_compute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:02 by gansari           #+#    #+#             */
/*   Updated: 2025/03/04 15:00:04 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	compute_mandelbrot(t_fractal *fract, t_complex *c)
{
	t_complex	z;
	double		re_temp;
	int			i;

	i = 0;
	z.re = 0;
	z.im = 0;
	while ((z.re * z.re + z.im * z.im) < 4 && i < fract->iterations)
	{
		re_temp = z.re * z.re - z.im * z.im + c->re;
		z.im = 2 * z.re * z.im + c->im;
		z.re = re_temp;
		i++;
	}
	return (i);
}

int	compute_julia(t_fractal *fract, t_complex *c, int x, int y)
{
	double		re_temp;
	t_complex	z;
	int			i;

	i = 0;
	z.re = (x / fract->zoom) + fract->offset_x;
	z.im = (y / fract->zoom) + fract->offset_y;
	while ((z.re * z.re + z.im * z.im) < 4 && i < fract->iterations)
	{
		re_temp = z.re * z.re - z.im * z.im + c->re;
		z.im = 2 * z.re * z.im + c->im;
		z.re = re_temp;
		i++;
	}
	return (i);
}

int	compute_burning_ship(t_fractal *fract, t_complex *c)
{
	t_complex	z;
	double		re_temp;
	int			i;

	i = 0;
	z.re = 0;
	z.im = 0;
	while ((z.re * z.re + z.im * z.im) < 4 && i < fract->iterations)
	{
		re_temp = z.re * z.re - z.im * z.im + c->re;
		z.im = fabs(2 * z.re * z.im + c->im);
		z.re = fabs(re_temp);
		i++;
	}
	return (i);
}

int	compute_tricorn(t_fractal *fract, t_complex *c)
{
	double		re_temp;
	t_complex	z;
	int			i;

	i = 0;
	z.re = 0;
	z.im = 0;
	while ((z.re * z.re + z.im * z.im) < 4 && i < fract->iterations)
	{
		re_temp = z.re * z.re - z.im * z.im + c->re;
		z.im = -2 * z.re * z.im + c->im;
		z.re = re_temp;
		i++;
	}
	return (i);
}
