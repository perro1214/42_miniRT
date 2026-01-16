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

// t_vec3 (x=R, y=G, z=B) を int 色に変換
int	vec3_to_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)color.x;
	g = (int)color.y;
	b = (int)color.z;
	return ((r << 16) | (g << 8) | b);
}
