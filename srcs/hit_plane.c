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
double	hit_plane(t_plane *plane, t_ray ray)
{
	double denominator; // 分母 (D · N)
	double t;           // 交差点までの距離
	t_vec3 p0_to_S;     // P0 - S
	// 分母を計算 (D · N)
	denominator = vec3_dot(ray.direction, plane->normal);
	if (fabs(denominator) < 1e-6)
	{
		// レイが平面に平行の場合、交差しない
		return (-1.0);
	}
	// t = ((P0 - S) · N) / (D · N)
	p0_to_S = vec3_sub(plane->point, ray.origin);
	t = vec3_dot(p0_to_S, plane->normal) / denominator;
	// tが負の場合、交差しない
	if (t < 0.0001)
	{
		return (-1.0);
	}
	return (t);
}
