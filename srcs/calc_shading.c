/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:30:05 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 16:30:09 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	calc_shading(t_hit_record *rec, t_ambient *ambient, t_light *light)
{
	t_vec3	result;

	result = calc_ambient(*ambient, rec->color);
	result = vec3_add(result, calc_diffuse(*light, rec->point, rec->normal,
				rec->color));
	result = clamp_color(result);
	return (denormalize_color(result));
}

static t_vec3	add_light_contrib(t_light *curr_light, t_hit_record *rec)
{
	t_vec3	diffuse_color;
	t_vec3	specular_color;

	diffuse_color = calc_diffuse(*curr_light, rec->point, rec->normal,
			rec->color);
	specular_color = calc_specular(*curr_light, rec->point, rec->normal,
			rec->view_dir);
	return (vec3_add(diffuse_color, specular_color));
}

t_vec3	calc_lighting(t_object *objects, t_ambient *ambient, t_light *light,
		t_hit_record *rec)
{
	t_vec3	result;
	t_light	*curr_light;

	result = calc_ambient(*ambient, rec->color);
	curr_light = light;
	while (curr_light)
	{
		if (!is_in_shadow(objects, curr_light, rec->point, rec->normal))
			result = vec3_add(result, add_light_contrib(curr_light, rec));
		curr_light = curr_light->next;
	}
	result = clamp_color(result);
	return (denormalize_color(result));
}
