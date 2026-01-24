/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:31:03 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/24 03:13:47 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// colorを [0, 255] から [0, 1] に変換する専用関数
t_vec3	color_to_unit(t_vec3 color)
{
	return ((t_vec3){color.x / 255.0, color.y / 255.0, color.z / 255.0});
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

// 色を0-255の範囲に変換
t_vec3	denormalize_color(t_vec3 color)
{
	return (vec3_scale(color, 255.0));
}

// 色のクランプ（0-1の範囲に）
t_vec3	clamp_color(t_vec3 color)
{
	t_vec3	result;

	result.x = fmin(fmax(color.x, 0.0), 1.0);
	result.y = fmin(fmax(color.y, 0.0), 1.0);
	result.z = fmin(fmax(color.z, 0.0), 1.0);
	return (result);
}
