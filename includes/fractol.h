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
# define MAX_ITERATIONS 256
# define DEFAULT_COLOR 655362
//# define DEFAULT_COLOR 983040
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
	double		mouse_x;
	double		mouse_y;
	double		offset_x;
	double		offset_y;
	int			iterations;
	bool		is_julia_lock;
}	t_fractal;

void	wrong_input(void);
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
int		on_mouse_move(int x, int y, t_fractal *fractal);
int		compute_burning_ship(t_fractal *fract, t_complex *c);
int		compute_tricorn(t_fractal *fract, t_complex *c);

# endif
