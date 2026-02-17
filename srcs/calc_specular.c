/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:29:46 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 16:30:23 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	vec3_reflect(t_vec3 light_dir, t_vec3 normal)
{
	double	n_dot_l;

	n_dot_l = vec3_dot(normal, light_dir);
	return (vec3_sub(vec3_scale(normal, 2.0 * n_dot_l), light_dir));
}

t_vec3	calc_specular(t_light light, t_vec3 hit_point,
		t_vec3 normal, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	double	r_dot_v;
	double	spec;

	light_dir = vec3_normalize(vec3_sub(light.curr.pos, hit_point));
	reflect_dir = vec3_reflect(light_dir, normal);
	r_dot_v = vec3_dot(reflect_dir, view_dir);
	if (r_dot_v < 0)
		return (vec3_init(0, 0, 0));
	spec = SPECULAR_COEFF * light.intensity * pow(r_dot_v, SHININESS);
	return (vec3_scale(light.color, spec));
}
