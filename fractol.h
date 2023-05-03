/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:15:11 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 13:42:00 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx_mms/mlx.h"
# include <math.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	double	xmin;
	double	xinc;
	double	ymin;
	double	yinc;

}			t_img;

typedef struct s_param
{
	int		set;
	int		arg;
	void	*mlx;
	void	*mlx_win;
	int		width;
	int		height;
	t_img	img;
	t_img	temp_img;
	int		(*plt[7])(int);
	int		pind;
}			t_param;

typedef struct s_mand
{
	double	cx;
	double	cy;
	double	zx;
	double	zy;
	double	x2;
	double	y2;
	double	w;
}			t_mand;

// int check_arg(int argc, char **argv);
int check_arg(t_param *param, int argc, char **argv);
int ft_strcmp(char *s1, char *s2);
int print_arg_error(void);
void fractol_init(t_param *param);
void set_pixel_color(t_img *img, int x, int y, int color);
int mandelbrot(int x, int y, t_img *img);
int julia(int x, int y, t_img *img, int arg);
double julia_preset(char c, int arg);
int tricone(int x, int y, t_img *img);
void init_plane(t_param *param);
void set_img_color(t_param *param, t_img *img);
int key_hook(int keycode, t_param *param);
int exit_on_destroy(void);
int mouse_hook(int button, int x, int y, t_param *param);
void zoom_in(t_param *param, int x, int y);
void zoom_out(t_param *param, int x, int y);
void clear_prev_img(t_param *param);
void vertical_move(t_param *param, int key);
void horizon_move(t_param *param, int key);
void init_palette(t_param *param);
int palette1(int color);
int palette2(int color);
int palette3(int color);
int palette4(int color);
int palette5(int color);
int palette6(int color);
int palette7(int color);
void new_palette(t_param *param);
void new_arg(t_param *param);

#endif
