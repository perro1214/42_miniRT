/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:38:44 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/17 16:30:41 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	check_cyl_hit(t_quadratic q, double dv, double wv,
		double height)
{
	double	m;

	if (q.t1 >= EPSILON)
	{
		m = dv * q.t1 + wv;
		if (m >= 0 && m <= height)
			return (q.t1);
	}
	if (q.t2 >= EPSILON)
	{
		m = dv * q.t2 + wv;
		if (m >= 0 && m <= height)
			return (q.t2);
	}
	return (-1.0);
}

static double	hit_cylinder_side(t_object *obj, t_ray ray)
{
	t_vec3		w;
	double		dv;
	double		wv;
	t_quadratic	q;

	w = vec3_sub(ray.origin, obj->curr.pos);
	dv = vec3_dot(ray.direction, obj->curr.normal);
	wv = vec3_dot(w, obj->curr.normal);
	q.a = 1.0 - (dv * dv);
	if (fabs(q.a) < EPSILON)
		return (-1.0);
	q.b = 2.0 * (vec3_dot(ray.direction, w) - (dv * wv));
	q.c = vec3_dot(w, w) - (wv * wv)
		- (obj->data.cy.radius * obj->data.cy.radius);
	if (!solve_quadratic(&q))
		return (-1.0);
	return (check_cyl_hit(q, dv, wv, obj->data.cy.height));
}

static double	hit_cylinder_caps(t_object *obj, t_ray ray)
{
	double	bottom;
	double	top;
	t_vec3	top_center;
	t_vec3	n;
	double	r;

	n = obj->curr.normal;
	r = obj->data.cy.radius;
	bottom = hit_disk(ray, obj->curr.pos, n, r);
	top_center = vec3_add(obj->curr.pos,
			vec3_scale(n, obj->data.cy.height));
	top = hit_disk(ray, top_center, n, r);
	if (bottom > EPSILON && (top < EPSILON || bottom < top))
		return (bottom);
	if (top > EPSILON)
		return (top);
	return (-1.0);
}

double	hit_cylinder(t_object *obj, t_ray ray)
{
	double	t_side;
	double	t_caps;

	t_side = hit_cylinder_side(obj, ray);
	t_caps = hit_cylinder_caps(obj, ray);
	if (t_side >= EPSILON && (t_caps <= EPSILON || t_side < t_caps))
		return (t_side);
	if (t_caps >= EPSILON)
		return (t_caps);
	return (-1.0);
}
