/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:04:33 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/17 01:22:09 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_in_shadow(t_object *objs, t_light *light, t_vec3 hit_point,
		t_vec3 normal)
{
	t_ray		shadow_ray;
	double		light_distance;
	double		t;
	t_object	*obj;

	light_distance = vec3_norm(vec3_sub(light->curr.pos, hit_point));
	shadow_ray.origin = vec3_add(hit_point, vec3_scale(normal, EPSILON));
	shadow_ray.direction = vec3_normalize(vec3_sub(light->curr.pos, hit_point));
	obj = objs;
	while (obj)
	{
		t = get_hit_distance(obj, shadow_ray);
		if (t > EPSILON && t < light_distance)
			return (1);
		obj = obj->next;
	}
	return (0);
}
