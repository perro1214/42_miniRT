/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:50:29 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 01:19:01 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	get_cylinder_normal(t_object *obj, t_vec3 hit_point);
static t_vec3	get_cone_normal(t_object *obj, t_vec3 hit_point);

t_object	*find_closest_obj(t_scene *scene, t_ray ray, double *out_t)
{
	t_object	*curr;
	t_object	*closest_obj;
	double		min_t;
	double		t;

	curr = scene->objs;
	closest_obj = NULL;
	min_t = INFINITY;
	while (curr)
	{
		t = get_hit_distance(curr, ray);
		if (t >= EPSILON && t < min_t)
		{
			min_t = t;
			closest_obj = curr;
		}
		curr = curr->next;
	}
	*out_t = min_t;
	return (closest_obj);
}

t_vec3	get_normal(t_object *obj, t_vec3 hit_point, t_vec3 ray_dir)
{
	t_vec3	normal;

	if (obj->type == SPHERE)
		normal = vec3_normalize(vec3_sub(hit_point, obj->curr.pos));
	else if (obj->type == PLANE)
		normal = obj->curr.normal;
	else if (obj->type == CYLINDER)
		normal = get_cylinder_normal(obj, hit_point);
	else if (obj->type == CONE)
		normal = get_cone_normal(obj, hit_point);
	else
		normal = vec3_init(0, 1, 0);
	if (vec3_dot(ray_dir, normal) > 0)
		return (vec3_scale(normal, -1.0));
	return (normal);
}

static t_vec3	get_cylinder_normal(t_object *obj, t_vec3 hit_point)
{
	t_vec3	cp;
	double	m;
	t_vec3	q;

	cp = vec3_sub(hit_point, obj->curr.pos);
	m = vec3_dot(cp, obj->curr.normal);
	if (m <= EPSILON)
		return (vec3_scale(obj->curr.normal, -1.0));
	if (m >= obj->data.cy.height - EPSILON)
		return (obj->curr.normal);
	q = vec3_scale(obj->curr.normal, m);
	return (vec3_normalize(vec3_sub(cp, q)));
}

static t_vec3	get_cone_normal(t_object *obj, t_vec3 hit_point)
{
	t_vec3	cp;
	t_vec3	tip;
	double	h;
	double	m;
	t_vec3	n;

	cp = vec3_sub(hit_point, obj->curr.pos);
	m = vec3_dot(cp, obj->curr.normal);
	if (m <= EPSILON)
		return (vec3_scale(obj->curr.normal, -1.0));
	tip = vec3_add(obj->curr.pos, vec3_scale(obj->curr.normal,
				obj->data.co.height));
	h = vec3_dot(vec3_sub(hit_point, tip), obj->curr.normal);
	n = vec3_sub(vec3_sub(hit_point, tip), vec3_scale(obj->curr.normal, (1.0
					+ obj->data.co.k_sq) * h));
	return (vec3_normalize(n));
}
