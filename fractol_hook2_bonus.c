/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hook2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 15:58:46 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	zoom_in(t_param *param, int x, int y)
{
	if ((param->img.xmin == param->img.xmin + param->img.xinc)
		|| (param->img.ymin == param->img.ymin + param->img.yinc))
		return ;
	param->temp_img.img = mlx_new_image(param->mlx, param->width,
			param->height);
	param->temp_img.addr = mlx_get_data_addr(param->temp_img.img,
			&(param->temp_img.bpp), &(param->temp_img.size_line),
			&(param->temp_img.endian));
	param->temp_img.xmin = param->img.xmin + x * param->img.xinc * 0.1;
	param->temp_img.xinc = param->img.xinc * 0.9;
	param->temp_img.ymin = param->img.ymin + (param->height - y - 1)
		* param->img.yinc * 0.1;
	param->temp_img.yinc = param->img.yinc * 0.9;
	set_img_color(param, &param->temp_img);
	mlx_put_image_to_window(param->mlx, param->mlx_win,
		param->temp_img.img, 0, 0);
	clear_prev_img(param);
}

void	zoom_out(t_param *param, int x, int y)
{
	if ((param->img.xinc >= 4) || (param->img.yinc >= 4))
		return ;
	param->temp_img.img = mlx_new_image(param->mlx, param->width,
			param->height);
	param->temp_img.addr = mlx_get_data_addr(param->temp_img.img,
			&(param->temp_img.bpp), &(param->temp_img.size_line),
			&(param->temp_img.endian));
	param->temp_img.xmin = param->img.xmin - x * param->img.xinc * 0.1;
	param->temp_img.xinc = param->img.xinc * 1.1;
	param->temp_img.ymin = param->img.ymin - (param->height - y - 1)
		* param->img.yinc * 0.1;
	param->temp_img.yinc = param->img.yinc * 1.1;
	set_img_color(param, &param->temp_img);
	mlx_put_image_to_window(param->mlx, param->mlx_win,
		param->temp_img.img, 0, 0);
	clear_prev_img(param);
}

void	clear_prev_img(t_param *param)
{
	mlx_destroy_image(param->mlx, param->img.img);
	param->img.img = param->temp_img.img;
	param->img.addr = param->temp_img.addr;
	param->img.bpp = param->temp_img.bpp;
	param->img.size_line = param->temp_img.size_line;
	param->img.endian = param->temp_img.endian;
	param->img.xmin = param->temp_img.xmin;
	param->img.xinc = param->temp_img.xinc;
	param->img.ymin = param->temp_img.ymin;
	param->img.yinc = param->temp_img.yinc;
}

void	new_arg(t_param *param)
{
	if (param->set != 1)
		return ;
	if (param->arg < 4)
		param->arg = param->arg + 1;
	else
		param->arg = 1;
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
