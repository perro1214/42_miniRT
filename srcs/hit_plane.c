/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:10:21 by hayato            #+#    #+#             */
/*   Updated: 2026/02/16 07:24:55 by htsutsum         ###   ########.fr       */
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
	denominator = vec3_dot(ray.direction, obj->curr.normal);
	if (fabs(denominator) <= EPSILON)
	{
		// レイが平面に平行の場合、交差しない
		return (-1.0);
	}
	// t = ((P0 - S) · N) / (D · N) (obj->point が平面上の点)
	p0_to_s = vec3_sub(obj->curr.pos, ray.origin);
	t = vec3_dot(p0_to_s, obj->curr.normal) / denominator;
	// tが負の場合、交差しない
	if (t < EPSILON)
	{
		return (-1.0);
	}
	return (t);
}
