/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:50:29 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 20:53:42 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_mlx_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	if (!(0 <= color && color <= 0xFFFFFF))
	{
		log_error("ft_mlx_put_pixel: color value out of range");
		return ;
	}
	*(unsigned int *)dst = color;
}

// color init

t_color	color_init(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

// 色の混合
t_color	color_multiply(t_color color_A, t_color color_B)
{
	t_color	result;

	result.r = (color_A.r * color_B.r) / 255;
	result.g = (color_A.g * color_B.g) / 255;
	result.b = (color_A.b * color_B.b) / 255;
	return (result);
}

t_color	color_scalar(t_color color, float scalar)
{
	t_color	result;

	result.r = (int)(color.r * scalar);
	result.g = (int)(color.g * scalar);
	result.b = (int)(color.b * scalar);

	return (result);
}

// RGB to int color
int	create_color(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}
