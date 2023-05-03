/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_palette2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:14:58 by joonhlee          #+#    #+#             */
/*   Updated: 2023/05/03 14:09:00 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
