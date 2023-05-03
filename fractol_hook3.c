/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hook3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 14:08:58 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	vertical_move(t_param *param, int key)
{
	int	direction;

	if ((param->img.ymin >= 3)
		|| (param->img.ymin + param->img.yinc * param->height <= -3))
		return ;
	direction = -2 * (key - 126) - 1;
	param->temp_img.img = mlx_new_image(param->mlx, param->width,
			param->height);
	param->temp_img.addr = mlx_get_data_addr(param->temp_img.img,
			&(param->temp_img.bpp), &(param->temp_img.size_line),
			&(param->temp_img.endian));
	param->temp_img.xmin = param->img.xmin;
	param->temp_img.xinc = param->img.xinc;
	param->temp_img.ymin = param->img.ymin
		+ direction * param->img.yinc * (param->height / 20);
	param->temp_img.yinc = param->img.yinc;
	set_img_color(param, &param->temp_img);
	mlx_put_image_to_window(param->mlx, param->mlx_win,
		param->temp_img.img, 0, 0);
	clear_prev_img(param);
}

void	horizon_move(t_param *param, int key)
{
	int	direction;

	if ((param->img.xmin >= 3)
		|| (param->img.xmin + param->img.xinc * param->width <= -3))
		return ;
	direction = 2 * (key - 123) - 1;
	param->temp_img.img = mlx_new_image(param->mlx, param->width,
			param->height);
	param->temp_img.addr = mlx_get_data_addr(param->temp_img.img,
			&(param->temp_img.bpp), &(param->temp_img.size_line),
			&(param->temp_img.endian));
	param->temp_img.xmin = param->img.xmin
		+ direction * param->img.xinc * (param->width / 20);
	param->temp_img.xinc = param->img.xinc;
	param->temp_img.ymin = param->img.ymin;
	param->temp_img.yinc = param->img.yinc;
	set_img_color(param, &param->temp_img);
	mlx_put_image_to_window(param->mlx, param->mlx_win,
		param->temp_img.img, 0, 0);
	clear_prev_img(param);
}

void	new_palette(t_param *param)
{
	param->pind = (param->pind + 1) % 7;
	param->temp_img.img = mlx_new_image(param->mlx, param->width,
			param->height);
	param->temp_img.addr = mlx_get_data_addr(param->temp_img.img,
			&(param->temp_img.bpp), &(param->temp_img.size_line),
			&(param->temp_img.endian));
	param->temp_img.xmin = param->img.xmin;
	param->temp_img.xinc = param->img.xinc;
	param->temp_img.ymin = param->img.ymin;
	param->temp_img.yinc = param->img.yinc;
	set_img_color(param, &param->temp_img);
	mlx_put_image_to_window(param->mlx, param->mlx_win,
		param->temp_img.img, 0, 0);
	clear_prev_img(param);
}

void	init_palette(t_param *param)
{
	param->plt[0] = &palette1;
	param->plt[1] = &palette2;
	param->plt[2] = &palette3;
	param->plt[3] = &palette4;
	param->plt[4] = &palette5;
	param->plt[5] = &palette6;
	param->plt[6] = &palette7;
	param->pind = 0;
}
