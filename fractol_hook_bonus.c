/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hook_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 15:58:43 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	key_hook(int keycode, t_param *param)
{
	if (keycode == 53)
	{
		mlx_destroy_window(param->mlx, param->mlx_win);
		mlx_destroy_image(param->mlx, param->img.img);
		exit (0);
	}
	if (keycode == 126 || keycode == 125)
		vertical_move(param, keycode);
	if (keycode == 123 || keycode == 124)
		horizon_move(param, keycode);
	if (keycode == 1)
		new_palette(param);
	if (keycode == 2)
		new_arg(param);
	return (0);
}

int	exit_on_destroy(t_param *param)
{
	mlx_destroy_image(param->mlx, param->img.img);
	exit(0);
}

int	mouse_hook(int button, int x, int y, t_param *param)
{
	int	i;

	i = x + y;
	if (button == 4)
		zoom_out(param, x, y);
	if (button == 5)
		zoom_in(param, x, y);
	return (0);
}
