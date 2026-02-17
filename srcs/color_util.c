/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 02:31:03 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/17 16:30:28 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	color_to_unit(t_vec3 color)
{
	return (vec3_init(color.x / 255.0, color.y / 255.0, color.z / 255.));
}

int	vec3_to_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = (int)color.x;
	g = (int)color.y;
	b = (int)color.z;
	return ((r << 16) | (g << 8) | b);
}

t_vec3	denormalize_color(t_vec3 color)
{
	return (vec3_scale(color, 255.0));
}

t_vec3	clamp_color(t_vec3 color)
{
	t_vec3	result;

	result.x = fmin(fmax(color.x, 0.0), 1.0);
	result.y = fmin(fmax(color.y, 0.0), 1.0);
	result.z = fmin(fmax(color.z, 0.0), 1.0);
	return (result);
}

t_vec3	get_checker_color(t_hit_record *rec, t_object *obj)
{
	t_vec3	p;
	double	u;
	double	v;
	double	inv_size;

	inv_size = 0.5;
	p = vec3_sub(rec->point, obj->curr.pos);
	u = vec3_dot(p, obj->right);
	v = vec3_dot(p, obj->up);
	if (((int)floor(u * inv_size) + (int)floor(v * inv_size)) % 2 == 0)
		return (obj->color);
	else
		return (vec3_init(1, 1, 1));
}
