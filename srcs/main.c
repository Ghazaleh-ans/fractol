#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal fractal;
	if (argc != 2)
		wrong_input();
	init_fractal(&fractal, argv[1]);
	render_fractal(&fractal);
	mlx_loop(fractal.mlx);
	return (0);
}
