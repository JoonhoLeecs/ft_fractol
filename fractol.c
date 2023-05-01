/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/01 21:01:05 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	int		set;
	void	*mlx;
	void	*mlx_win;
	t_img	img;

	set = check_arg(argc, argv);
	if (set < 0)
		return (print_arg_error());
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1600, 1600, "Fract'ol");
	img.img = mlx_new_image(mlx, 1600, 1600);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line,
			&img.endian);
	init_plane(&img, set, 1600, 1600);
	set_img_color(&img, 1600, 1600);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);


}

int	print_arg_error(void)
{
	ft_putstr_fd("Invalid argument\n", 1);
	ft_putstr_fd("Mandelbrot set: Mandelbrot\n", 1);
	ft_putstr_fd("Julia set: Julia\n", 1);
	return (1);
}

int	check_arg(int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	if (ft_strcmp("Mandelbrot", argv[1]) == 0)
		return (0);
	else if (ft_strcmp("Julia", argv[1]) == 0)
		return (1);
	else
		return (-1);
}

void	set_pixel_color(t_img *img, int x, int y, int color)
{
	char	*dst;

	// color = (color >= 0) * color + (color < 0) * (color + 2147483648);
	dst = img->addr + y * img->size_line + x * img->bpp / 8;
	*(unsigned int *)dst = color;
}

void	set_img_color(t_img *img, int width, int height)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < width)
	{
		y = 0;
		while (y < height)
		{
			color = mandelbrot(x, y, img);
			set_pixel_color(img, x, y, color);
			y++;
		}
		x++;
	}
}

int	mandelbrot(int x, int y, t_img *img)
{
	int	iter;
	double	cx;
	double	cy;
	double	zx;
	double	zy;
	double x2;
	double y2;
	double w;

	cx = img->xmin + (double)x * img->xinc;
	cy = img->ymin + (double)y * img->yinc;
	iter = 0;
	zx = 0;
	zy = 0;
	x2 = 0;
	y2 = 0;
	w = 0;
	while (x2 + y2 <= 4 && iter < 1023)
	{
		zx = x2 - y2 + cx;
		zy = w + cy;
		x2 = zx * zx;
		y2 = zy * zy;
		w = 2 * zx * zy;
		iter++;
	}
	// printf("iter:%d|", iter);
	// printf("color:%d\n", (iter / 4) | (iter / 4) << 8 | (iter / 4) << 16);
	return (255 - (iter / 4));
	// return ((iter / 4) | (iter / 4) << 8 | (iter / 4) << 16);
}

void	init_plane(t_img *img, int set, int width, int height)
{
	if (set != 0)
		return ;
	img->xmin = -2.5;
	img->ymin = -1;
	img->xinc = 3.5 / (double) width;
	img->yinc = 2 / (double) height;

	// printf("%f, %f, %f, %f\n", img->xmin, img->xinc, img->ymin, img->yinc);
}

