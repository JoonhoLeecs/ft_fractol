/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_set_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 15:59:04 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	mandelbrot(int x, int y, t_img *img)
{
	int		iter;
	t_mand	mand;

	mand.cx = img->xmin + (double)x * img->xinc;
	mand.cy = img->ymin + (double)y * img->yinc;
	iter = 0;
	mand.zx = 0;
	mand.zy = 0;
	mand.x2 = 0;
	mand.y2 = 0;
	mand.w = 0;
	while (mand.x2 + mand.y2 <= 4 && iter < 255)
	{
		mand.zx = mand.x2 - mand.y2 + mand.cx;
		mand.zy = mand.w + mand.cy;
		mand.x2 = mand.zx * mand.zx;
		mand.y2 = mand.zy * mand.zy;
		mand.w = 2 * mand.zx * mand.zy;
		iter++;
	}
	return (255 - iter);
}

int	julia(int x, int y, t_img *img, int arg)
{
	int		iter;
	t_mand	julia;

	julia.cx = julia_preset('x', arg);
	julia.cy = julia_preset('y', arg);
	iter = 0;
	julia.zx = img->xmin + (double)x * img->xinc;
	julia.zy = img->ymin + (double)y * img->yinc;
	julia.x2 = julia.zx * julia.zx;
	julia.y2 = julia.zy * julia.zy;
	julia.w = 2 * julia.zx * julia.zy;
	while (julia.x2 + julia.y2 <= 4 && iter < 255)
	{
		julia.zx = julia.x2 - julia.y2 + julia.cx;
		julia.zy = julia.w + julia.cy;
		julia.x2 = julia.zx * julia.zx;
		julia.y2 = julia.zy * julia.zy;
		julia.w = 2 * julia.zx * julia.zy;
		iter++;
	}
	return (255 - iter);
}

double	julia_preset(char c, int arg)
{
	if (arg == 1 && c == 'x')
		return (-0.4);
	else if (arg == 1 && c == 'y')
		return (0.6);
	else if (arg == 2 && c == 'x')
		return (0.285);
	else if (arg == 2 && c == 'y')
		return (0.01);
	else if (arg == 3 && c == 'x')
		return (-0.8);
	else if (arg == 3 && c == 'y')
		return (-0.156);
	else if (arg == 4 && c == 'x')
		return (-0.7269);
	else if (arg == 4 && c == 'y')
		return (0.1889);
	else
		return (4);
}

int	tricone(int x, int y, t_img *img)
{
	int		iter;
	t_mand	tric;

	tric.cx = img->xmin + (double)x * img->xinc;
	tric.cy = img->ymin + (double)y * img->yinc;
	iter = 0;
	tric.zx = 0;
	tric.zy = 0;
	tric.x2 = 0;
	tric.y2 = 0;
	tric.w = 0;
	while (tric.x2 + tric.y2 <= 4 && iter < 255)
	{
		tric.zx = tric.x2 - tric.y2 + tric.cx;
		tric.zy = tric.w + tric.cy;
		tric.x2 = tric.zx * tric.zx;
		tric.y2 = tric.zy * tric.zy;
		tric.w = -2 * tric.zx * tric.zy;
		iter++;
	}
	return (255 - iter);
}
