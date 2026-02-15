/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:31:35 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/16 07:25:04 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// 2次方程式を解く戦勝のヘルパー関数
// 2次方程式 at^2 + bt + c = 0 を解く。
// t1 (レイが最初に円柱の表面に接触する場所、t2はレイが円柱の中に入り、反対側に接触する場所
// 負の解しかない場合は 0,
int	solve_quadratic(double a, double b, double c, double *t1, double *t2)
{
	double	d;
	double	inv_2a;

	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (0);
	inv_2a = 0.5 / a;
	*t1 = (-b - sqrt(d)) * inv_2a;
	*t2 = (-b + sqrt(d)) * inv_2a;
	return (1);
}

// 円柱の蓋の部分の交差判定をするヘルパー関数
double	hit_disk(t_ray ray, t_vec3 center, t_vec3 normal, double radius)
{
	double	d;
	double	t;
	t_vec3	oc;
	t_vec3	v;

	d = vec3_dot(normal, ray.direction);
	if (fabs(d) <= EPSILON)
		return (-1.0);
	oc = vec3_sub(center, ray.origin);
	t = vec3_dot(oc, normal) / d;
	if (t < EPSILON)
		return (-1.0);
	v = vec3_sub(vec3_add(ray.origin, vec3_scale(ray.direction, t)), center);
	if (vec3_dot(v, v) > radius * radius)
		return (-1.0);
	return (t);
}
