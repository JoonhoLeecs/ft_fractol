/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:15:11 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/01 20:32:37 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx_mms/mlx.h"
# include <stdio.h>

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

int check_arg(int argc, char **argv);
int ft_strcmp(char *s1, char *s2);
int print_arg_error(void);
void set_pixel_color(t_img *img, int x, int y, int color);
void set_img_color(t_img *img, int width, int height);
int mandelbrot(int x, int y, t_img *img);
void init_plane(t_img *img, int set, int width, int height);

#endif
