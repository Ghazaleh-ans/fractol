/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:34:10 by gansari           #+#    #+#             */
/*   Updated: 2025/03/04 15:34:12 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include "keys.h"
# include "mlx.h"
# include "libft.h"

# define MANDELBROT "mandelbrot"
# define JULIA "julia"
# define BURNINGSHIP "burningship"
# define TRICORN "tricorn"
# define WIN_SIZE 526
# define VIEW_CHANGE_SIZE 60
# define MIN_ITERATIONS 256
# define MAX_ITERATIONS 2048
# define DEFAULT_COLOR 655362
# define SCALE 2
# define FIXED_RADIUS 1
# define MINIMUM_RADIUS 0.5

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_fractal
{
	char		*name;
	void		*mlx;
	void		*window;
	t_image		image;
	double		zoom;
	u_int32_t	color;
	double		julia_x;
	double		julia_y;
	double		offset_x;
	double		offset_y;
	int			iterations;
}	t_fractal;

void	help_input(void);
void	error_message(char *str);
int		compute_fractal(t_fractal *fract, t_complex *c, int x, int y);
void	render_fractal(t_fractal *fractal);
int		compute_mandelbrot(t_fractal *fract, t_complex *c);
int		compute_julia(t_fractal *fract, t_complex *c, int x, int y);
void	init_fractal(t_fractal *fractal, char *name);
void	set_fractal(t_fractal *fractal, char *name);
void	reset_fractal(t_fractal *fractal, char *fractal_name);
void	set_pixel_color(t_fractal *fractal, int x, int y, int color);
void	handle_move(int key, t_fractal *fractal);
int		on_key_press(int key, t_fractal *fractal);
int		on_destroy(t_fractal *engine);
int		on_mouse_scroll(int key, int x, int y, t_fractal *fractal);
void	change_color(int key, t_fractal *fractal);
int		compute_burning_ship(t_fractal *fract, t_complex *c);
int		compute_tricorn(t_fractal *fract, t_complex *c);
void	check_input(int argc, char **argv, t_fractal *fractal);
void	wrong_julia_input(void);
void	check_julia_input(char *str);
void	init_window(t_fractal *fractal);
void	init_image(t_fractal *fractal);
void	set_image_address(t_fractal *fractal);

#endif
