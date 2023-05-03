/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 13:35:48 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	ft_putstr_fd("Invalid argument\n", 1);
	ft_putstr_fd("Mandelbrot set: Mandelbrot\n", 1);
	ft_putstr_fd("Julia set: Julia arg(1 - 4)\n", 1);
	ft_putstr_fd("Tricone set: Tricone\n", 1);
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

void	set_pixel_color(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + y * img->size_line + x * img->bpp / 8;
	*(unsigned int *)dst = color;
}

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

int	exit_on_destroy(void)
{
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


int	palette1(int color)
{
	float	r;
	int		v;

	r = powf((float)color, 1.5);
	v = (int) r % 256;
	v = v << 16 | 70 | color << 8;
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
	v = v << 8 | 80 << 16 | color;
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

//mint-choco
int	palette5(int color)
{
	return (color << 8 | color);
}
//yellow
int	palette6(int color)
{
	return (color << 16 | color << 8);
}
//white
int	palette7(int color)
{
	return (color << 16 | color << 8 | color);
}
