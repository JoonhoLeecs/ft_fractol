/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 15:58:38 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	main(int argc, char **argv)
{
	t_param	param;

	param.set = check_arg(&param, argc, argv);
	if (param.set < 0)
		return (print_arg_error());
	fractol_init(&param);
	mlx_put_image_to_window(param.mlx, param.mlx_win, param.img.img, 0, 0);
	mlx_hook(param.mlx_win, 17, 0L, &exit_on_destroy, &param);
	mlx_key_hook(param.mlx_win, &key_hook, &param);
	mlx_mouse_hook(param.mlx_win, &mouse_hook, &param);
	mlx_loop(param.mlx);
}

int	check_arg(t_param *param, int argc, char **argv)
{
	int	arg;

	if (!(argc >= 2 && argc <= 3))
		return (-1);
	if (ft_strcmp("Mandelbrot", argv[1]) == 0 && argc == 2)
		return (0);
	else if (ft_strcmp("Julia", argv[1]) == 0 && argc == 3)
	{
		arg = ft_atoi(argv[2]);
		if (arg < 1 || arg > 4)
			return (-1);
		param->arg = arg;
		return (1);
	}
	else if (ft_strcmp("Tricone", argv[1]) == 0 && argc == 2)
		return (2);
	else
		return (-1);
}

int	print_arg_error(void)
{
	ft_putstr_fd("Invalid argument\n", 2);
	ft_putstr_fd("Mandelbrot set: Mandelbrot\n", 2);
	ft_putstr_fd("Julia set: Julia arg(1 - 4)\n", 2);
	ft_putstr_fd("Tricone set: Tricone\n", 2);
	return (1);
}

void	fractol_init(t_param *param)
{
	param->mlx = mlx_init();
	param->width = 620;
	param->height = 560;
	param->mlx_win = mlx_new_window(param->mlx, param->width, param->height,
			"Fract'ol");
	param->img.img = mlx_new_image(param->mlx, param->width, param->height);
	param->img.addr = mlx_get_data_addr(param->img.img, &(param->img.bpp),
			&(param->img.size_line), &(param->img.endian));
	init_palette(param);
	init_plane(param);
}
