/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_palette_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 15:58:55 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	palette1(int color)
{
	float	r;
	int		v;

	r = powf((float)color, 1.5);
	v = (int) r % 256;
	v = v << 8 | 80 << 16 | color;
	return (v);
}

int	palette2(int color)
{
	int	v;

	v = (color * color) % 256;
	v = v << 8 | 100 | color << 16;
	return (v);
}

int	palette3(int color)
{
	float	r;
	int		v;

	r = powf((float)color, 1.5);
	v = (int) r % 256;
	v = v << 16 | 70 | color << 8;
	return (v);
}

int	palette4(int color)
{
	int		v;
	float	r;
	int		x;

	v = (color * color) % 256;
	r = powf((float)color, 1.5);
	x = (int)r % 256;
	v = v << 16 | x | color << 8;
	return (v);
}
