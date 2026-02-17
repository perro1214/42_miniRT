/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:50:13 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 16:29:39 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	calc_diffuse(t_light light, t_vec3 hit_point, t_vec3 normal,
		t_vec3 object_color)
{
	t_vec3	light_dir;
	double	n_dot_l;
	t_vec3	diffuse_light;

	light_dir = vec3_normalize(vec3_sub(light.curr.pos, hit_point));
	n_dot_l = vec3_dot(normal, light_dir);
	if (n_dot_l < 0)
		n_dot_l = 0;
	diffuse_light = vec3_multiply(object_color, light.color);
	diffuse_light = vec3_scale(diffuse_light, light.intensity * n_dot_l);
	return (diffuse_light);
}
