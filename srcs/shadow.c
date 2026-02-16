/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:04:33 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/17 00:22:13 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_in_shadow(t_object *obj, t_light *light, t_vec3 hit_point,
		t_vec3 normal)
{
	t_ray		shadow_ray;
	double		light_distance;
	double		t;

	light_distance = vec3_norm(vec3_sub(light->curr.pos, hit_point));
	shadow_ray.origin = vec3_add(hit_point, vec3_scale(normal, EPSILON));
	shadow_ray.direction = vec3_normalize(vec3_sub(light->curr.pos, hit_point));
	while (obj)
	{
		if (obj->type == SPHERE)
			t = hit_sphere(obj, shadow_ray);
		else if (obj->type == PLANE)
			t = hit_plane(obj, shadow_ray);
		else if (obj->type == CYLINDER)
			t = hit_cylinder(obj, shadow_ray);
		else if (obj->type == CONE)
			t = hit_cone(obj, shadow_ray);
		else
			t = -1;
		if (t > EPSILON && t < light_distance)
			return (1);
		obj = obj->next;
	}
	return (0);
}
