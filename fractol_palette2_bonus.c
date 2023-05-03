/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_palette2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 16:02:41 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	palette5(int color)
{
	return (color << 8 | color);
}

int	palette6(int color)
{
	return (color << 16 | color << 8);
}

int	palette7(int color)
{
	return (color << 16 | color << 8 | color);
}
