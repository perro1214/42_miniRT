/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:10:21 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 16:30:45 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_plane(t_object *obj, t_ray ray)
{
	double	denominator;
	double	t;
	t_vec3	p0_to_s;

	denominator = vec3_dot(ray.direction, obj->curr.normal);
	if (fabs(denominator) <= EPSILON)
		return (-1.0);
	p0_to_s = vec3_sub(obj->curr.pos, ray.origin);
	t = vec3_dot(p0_to_s, obj->curr.normal) / denominator;
	if (t < EPSILON)
		return (-1.0);
	return (t);
}
