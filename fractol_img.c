/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 14:08:58 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_plane(t_param *param)
{
	if (param->set == 0)
	{
		param->img.xmin = -2;
		param->img.ymin = -1.12;
		param->img.xinc = 2.47 / (double) param->width;
		param->img.yinc = 2.24 / (double) param->height;
		set_img_color(param, &param->img);
	}
	else if (param->set == 1)
	{
		param->img.xmin = -1.24;
		param->img.ymin = -1.12;
		param->img.xinc = 2.47 / (double) param->width;
		param->img.yinc = 2.24 / (double) param->height;
		set_img_color(param, &param->img);
	}
	else
	{
		param->img.xmin = -1.48;
		param->img.ymin = -1.24;
		param->img.xinc = 2.72 / (double) param->width;
		param->img.yinc = 2.48 / (double) param->height;
		set_img_color(param, &param->img);
	}
}

void	set_img_color(t_param *param, t_img *img)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < param->width)
	{
		y = 0;
		while (y < param->height)
		{
			if (param->set == 0)
				color = mandelbrot(x, y, img);
			else if (param->set == 1)
				color = julia(x, y, img, param->arg);
			else
				color = tricone(x, y, img);
			color = param->plt[param->pind](color);
			set_pixel_color(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	set_pixel_color(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + y * img->size_line + x * img->bpp / 8;
	*(unsigned int *)dst = color;
}
