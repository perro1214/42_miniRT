/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:38:44 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/10 18:03:33 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	hit_cylinder_caps(t_object *obj, t_ray ray);
static double	hit_cylinder_side(t_object *obj, t_ray ray);

double	hit_cylinder(t_object *obj, t_ray ray)
{
	double	t_side;
	double	t_caps;

	t_side = hit_cylinder_side(obj, ray);
	t_caps = hit_cylinder_caps(obj, ray);

	// 側面と蓋のうち、より手前にある交点（最小のt）を採用
	if (t_side > EPSILON && (t_caps < EPSILON || t_side < t_caps))
		return (t_side);
	if (t_caps > EPSILON)
		return (t_caps);

	return (-1.0);
}

// a = D・D - (D・V)^2
// b = 2 * (D・W - (D・V)(W・V))
// c = W・W - (W・V)^2 - r^2
// V: 円柱の方向ベクトル(単位ベクトル), W: レイ始点から円柱位置へのベクトル
static double	hit_cylinder_side(t_object *obj, t_ray ray)
{
	t_vec3	w = vec3_sub(ray.origin, obj->pos);
	double	dv; // ray.direction と v の内積
	double	wv; // w と v の内積
	double	a, b, c, t1, t2;

	// 正規化済み前提の最適化
	dv = vec3_dot(ray.direction, obj->data.cy.normal);
	wv = vec3_dot(w, obj->data.cy.normal);
	// a = 1.0 - (D・V)^2  (ray.directionが正規されているため、 D・D は 1.0)
	a = 1.0 - (dv * dv);
	if (fabs(a) < EPSILON) // 軸と平行な場合は側面には当たらない
		return (-1.0);
	// b = 2 * (D・W - (D・V)(W・V))
	b = 2.0 * (vec3_dot(ray.direction, w) - (dv * wv));
	// c = W・W - (W・V)^2 - r^2
	c = vec3_dot(w, w) - (wv * wv) - (obj->data.cy.radius * obj->data.cy.radius);
	if (!solve_quadratic(a, b, c, &t1, &t2))
		return (-1.0);
	// 小さい方の解 t1 (手前の壁) の検証
	if (t1 > EPSILON)
	{
		double m1 = dv * t1 + wv;
		if (m1 >= 0 && m1 <= obj->data.cy.height)
			return (t1);
	}
	// 大きい方の解 t2 (奥の壁) の検証
	if (t2 > EPSILON)
	{
		double m2 = dv * t2 + wv;
		if (m2 >= 0 && m2 <= obj->data.cy.height)
			return (t2);
	}
	return (-1.0);
}

static double	hit_cylinder_caps(t_object *obj, t_ray ray)
{
	double	bottom;
	double	top;
	t_vec3	top_center;
	t_vec3	n;
	double	r;

	n = obj->data.cy.normal;
	r = obj->data.cy.radius;

	// 底面の判定
	bottom = hit_disk(ray, obj->pos, n, r);
	// 上面の判定 (上面中心 = 底面中心 + normal * height)
	top_center = vec3_add(obj->pos, vec3_scale(n, obj->data.cy.height));
	top = hit_disk(ray, top_center, n, r);
	// 両方の候補から最小の正の値を返す
	if (bottom > EPSILON && (top < EPSILON || bottom < top))
		return (bottom);
	if (top > EPSILON)
		return (top);
	return (-1.0);
}
