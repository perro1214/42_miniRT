/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:38:44 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/16 08:51:59 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	hit_cone_cap(t_object *obj, t_ray ray);
static double	hit_cone_side(t_object *obj, t_ray ray);

double	hit_cone(t_object *obj, t_ray ray)
{
	double	t_side;
	double	t_cap;

	t_side = hit_cone_side(obj, ray);
	t_cap = hit_cone_cap(obj, ray);

	// 側面と蓋のうち、より手前にある交点（最小のt）を採用
	if (t_side >= EPSILON && (t_cap <= EPSILON || t_side < t_cap))
		return (t_side);
	if (t_cap >= EPSILON)
		return (t_cap);
	return (-1.0);
}

// 円錐の交差判定（頂点を位置とする)
// a = D・D - (1 + k^2)(D・V)^2
// b = 2 * (D・W - (1 + k^2)(D・V)(W・V))
// c = W・W - (1 + k^2)(W・V)^2
// D; レイの方向ベクトル
// V: 円錐の方向ベクトル(単位ベクトル), W: レイ始点から頂点へのベクトル
static double	hit_cone_side(t_object *obj, t_ray ray)
{
	t_vec3 		tip;
	t_vec3		w;
	double		dv; // ray.direction と v の内積
	double		wv; // w と v の内積
	t_quadratic q;
	double		m;
	double		h1, h2;

	tip = vec3_add(obj->curr.pos, vec3_scale(obj->curr.normal, obj->data.co.height));
	w = vec3_sub(ray.origin, tip);
	// 正規化済み前提の最適化
	dv = vec3_dot(ray.direction, obj->curr.normal);
	wv = vec3_dot(w, obj->curr.normal);
	m = 1.0 + obj->data.co.k_sq;
	// a = 1.0 - (1 + k^2)(D・V)^2  (ray.directionが正規されているため、 D・D は 1.0)
	q.a = 1.0 - m * (dv * dv);
	// a = 0 は、レイが円錐の斜面（母線）と平行
	//	ゼロ除算を避けるため、および平行なレイは側面を貫通しないため除外
	if (fabs(q.a) < EPSILON)
		return (-1.0);
	// b = 2 * (D・W - (1 + k^2)(D・V)(W・V))
	q.b = 2.0 * (vec3_dot(ray.direction, w) - m * (dv * wv));
	// c = W・W - (1 + k^2)(W・V)^2
	q.c = vec3_dot(w, w) - m * (wv * wv);
	if (!solve_quadratic(&q))
		return (-1.0);

	// 交点の検証
	// 交点 P が頂点から底面までの「高さの範囲内」にあるかチェック
	// 頂点(tip)が 0、底面(base)が -height
	// 小さい方の解 t1 (手前の壁) の検証
	// 高さの範囲で制限しないと砂時計のようになる。
	if (q.t1 >= EPSILON)
	{
		h1 = dv * q.t1 + wv;
		if (h1 >= -obj->data.co.height && h1 <= 0)
			return (q.t1);
	}
	// 大きい方の解 t2 (奥の壁) の検証
	if (q.t2 >= EPSILON)
	{
		h2 = dv * q.t2 + wv;
		if (h2 >= -obj->data.co.height && h2 <= 0)
			return (q.t2);
	}
	return (-1.0);
}

static double	hit_cone_cap(t_object *obj, t_ray ray)
{
	double	bottom;
	t_vec3	n;
	double	r;

	n = obj->curr.normal;
	r = obj->data.co.radius;
	// 底面の判定
	bottom = hit_disk(ray, obj->curr.pos, n, r);
	if (bottom >= EPSILON)
		return (bottom);
	return (-1.0);
}
