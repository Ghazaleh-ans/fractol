/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gansari <gansari@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:00:46 by gansari           #+#    #+#             */
/*   Updated: 2025/03/04 15:00:48 by gansari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_message(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}

void	wrong_input(void)
{
	ft_putstr_fd("Error: Invalid arguments\n", 2);
	ft_putstr_fd("Please use: ./fractol mandelbrot or\n", 2);
	ft_putstr_fd("Please use: ./fractol julia RE IM or\n", 2);
	ft_putstr_fd("Please use: ./fractol burningship or\n", 2);
	ft_putstr_fd("Please use: ./fractol tricorn\n", 2);
	exit(EXIT_FAILURE);
}

void	wrong_julia_input(void)
{
	ft_putstr_fd("Error: Invalid arguments\n", 2);
	ft_putstr_fd("Please enter a valid point as input for julia set\n", 2);
	ft_putstr_fd("Please use: ./ fractol julia RE IM\n", 2);
	ft_putstr_fd("RE and IM are respectivly real and imaginary ", 2);
	ft_putstr_fd("part of the desired point.\n", 2);
	exit(EXIT_FAILURE);
}

void	check_julia_input(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		i++;
	}
	if (dot > 1)
		wrong_julia_input();
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) || str[i] == '.')
			i++;
		else
			wrong_julia_input();
	}
}

void	check_input(int argc, char **argv, t_fractal *fractal)
{
	if (argc == 2 && ft_strcmp(argv[1], JULIA))
		return ;
	else if (argc == 4)
	{
		if (ft_strcmp(argv[1], JULIA) == 0)
		{
			check_julia_input(argv[2]);
			check_julia_input(argv[3]);
			fractal->julia_x = ft_atof(argv[2]);
			fractal->julia_y = ft_atof(argv[3]);
			return ;
		}
	}
	wrong_input();
}
