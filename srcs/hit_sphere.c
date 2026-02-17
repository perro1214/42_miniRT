/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:32:26 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 16:30:53 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	calculate_discriminant(t_vec3 oc, t_ray ray, double radius)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	c = vec3_dot(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	return (discriminant);
}

static double	calculate_t(t_vec3 oc, t_ray ray, double dis)
{
	double	t1;
	double	t2;
	double	a;
	double	b;

	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	t1 = (-b - sqrt(dis)) / (2.0 * a);
	t2 = (-b + sqrt(dis)) / (2.0 * a);
	if (t1 >= 0.0001)
		return (t1);
	else if (t2 >= 0.0001)
		return (t2);
	return (-1.0);
}

double	hit_sphere(t_object *obj, t_ray ray)
{
	double	discriminant;
	double	t;
	t_vec3	oc;

	oc = vec3_sub(ray.origin, obj->curr.pos);
	discriminant = calculate_discriminant(oc, ray, obj->data.sp.radius);
	if (discriminant < 0)
		return (-1.0);
	t = calculate_t(oc, ray, discriminant);
	if (discriminant < 0)
		return (-1.0);
	return (t);
}
