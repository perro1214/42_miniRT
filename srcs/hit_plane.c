/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:10:21 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 22:15:14 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// 平面とレイの交差判定を行う関数
double	hit_plane(t_object *obj, t_ray ray)
{
	double	denominator;
	double	t;
	t_vec3	p0_to_s;

	// 分母を計算 (D · N)
	denominator = vec3_dot(ray.direction, obj->data.pl.normal);
	if (fabs(denominator) < 1e-6)
	{
		// レイが平面に平行の場合、交差しない
		return (-1.0);
	}
	// t = ((P0 - S) · N) / (D · N) (obj->point が平面上の点)
	p0_to_s = vec3_sub(obj->point, ray.origin);
	t = vec3_dot(p0_to_s, obj->data.pl.normal) / denominator;
	// tが負の場合、交差しない
	if (t < 0.0001)
	{
		return (-1.0);
	}
	return (t);
}
