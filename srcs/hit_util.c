/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 12:31:35 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/17 00:44:56 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// 2次方程式を解く戦勝のヘルパー関数
// 2次方程式 at^2 + bt + c = 0 を解く。
// t1 (レイが最初に円柱の表面に接触する場所、t2はレイが円柱の中に入り、反対側に接触する場所
// 負の解しかない場合は 0,
int	solve_quadratic(t_quadratic *q)
{
	double	d;
	double	inv_2a;

	d = q->b * q->b - 4.0 * q->a * q->c;
	if (d < 0)
		return (0);
	inv_2a = 0.5 / q->a;
	q->t1 = (-q->b - sqrt(d)) * inv_2a;
	q->t2 = (-q->b + sqrt(d)) * inv_2a;
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

double	get_hit_distance(t_object *obj, t_ray ray)
{
	if (obj->type == SPHERE)
		return (hit_sphere(obj, ray));
	if (obj->type == PLANE)
		return (hit_plane(obj, ray));
	if (obj->type == CYLINDER)
		return (hit_cylinder(obj, ray));
	if (obj->type == CONE)
		return (hit_cone(obj, ray));
	return (-1.0);
}
