/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:31:03 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/15 05:51:41 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// colorを [0, 255] から [0, 1] に変換する専用関数
t_vec3	color_to_unit(t_vec3 color)
{
	return (vec3_init(color.x / 255.0, color.y / 255.0, color.z / 255.));
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


//チェッカーカラー (平面のみ）
t_vec3 get_checker_color(t_hit_record *rec, t_object *obj)
{
	t_vec3	p;
	double	u;
	double	v;
	double 	size;

	size = 2.0;
	p = vec3_sub(rec->point, obj->curr.pos);
	u = vec3_dot(p, obj->right);
	v = vec3_dot(p, obj->up);
	if (((int)floor( u / size) + (int)floor(v / size)) % 2 == 0)
		return (obj->color);
	else
		return (vec3_init(1, 1, 1));
}
