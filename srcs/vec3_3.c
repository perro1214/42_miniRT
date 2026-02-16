/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:18:58 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 00:02:22 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_rotate_x(t_vec3 v, double angle)
{
	t_vec3	res;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	res.x = v.x;
	res.y = v.y * c - v.z * s;
	res.z = v.y * s + v.z * c;
	return (res);
}

t_vec3	vec3_rotate_y(t_vec3 v, double angle)
{
	t_vec3	res;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	res.x = v.x * c + v.z * s;
	res.y = v.y;
	res.z = -v.x * s + v.z * c;
	return (res);
}

t_vec3	vec3_rotate_z(t_vec3 v, double angle)
{
	t_vec3	res;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	res.x = v.x * c - v.y * s;
	res.y = v.x * s + v.y * c;
	res.z = v.z;
	return (res);
}

t_vec3	vec3_rotate_axis(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	term1 = vec3_scale(v, c);
	term2 = vec3_scale(vec3_cross(axis, v), s);
	term3 = vec3_scale(axis, vec3_dot(axis, v) * (1.0 - c));
	return (vec3_add(vec3_add(term1, term2), term3));
}
