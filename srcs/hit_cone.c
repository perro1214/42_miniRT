/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:38:44 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/17 16:30:38 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	check_cone_hit(t_quadratic q, double dv, double wv,
		double height)
{
	double	h;

	if (q.t1 >= EPSILON)
	{
		h = dv * q.t1 + wv;
		if (h >= -height && h <= 0)
			return (q.t1);
	}
	if (q.t2 >= EPSILON)
	{
		h = dv * q.t2 + wv;
		if (h >= -height && h <= 0)
			return (q.t2);
	}
	return (-1.0);
}

static double	hit_cone_side(t_object *obj, t_ray ray)
{
	t_vec3		tip;
	t_vec3		w;
	double		dv;
	double		wv;
	t_quadratic	q;

	tip = vec3_add(obj->curr.pos,
			vec3_scale(obj->curr.normal, obj->data.co.height));
	w = vec3_sub(ray.origin, tip);
	dv = vec3_dot(ray.direction, obj->curr.normal);
	wv = vec3_dot(w, obj->curr.normal);
	q.a = 1.0 - (1.0 + obj->data.co.k_sq) * (dv * dv);
	if (fabs(q.a) < EPSILON)
		return (-1.0);
	q.b = 2.0 * (vec3_dot(ray.direction, w)
			- (1.0 + obj->data.co.k_sq) * (dv * wv));
	q.c = vec3_dot(w, w) - (1.0 + obj->data.co.k_sq) * (wv * wv);
	if (!solve_quadratic(&q))
		return (-1.0);
	return (check_cone_hit(q, dv, wv, obj->data.co.height));
}

static double	hit_cone_cap(t_object *obj, t_ray ray)
{
	double	bottom;
	t_vec3	n;
	double	r;

	n = obj->curr.normal;
	r = obj->data.co.radius;
	bottom = hit_disk(ray, obj->curr.pos, n, r);
	if (bottom >= EPSILON)
		return (bottom);
	return (-1.0);
}

double	hit_cone(t_object *obj, t_ray ray)
{
	double	t_side;
	double	t_cap;

	t_side = hit_cone_side(obj, ray);
	t_cap = hit_cone_cap(obj, ray);
	if (t_side >= EPSILON && (t_cap <= EPSILON || t_side < t_cap))
		return (t_side);
	if (t_cap >= EPSILON)
		return (t_cap);
	return (-1.0);
}
