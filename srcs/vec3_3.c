/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:18:58 by hayato            #+#    #+#             */
/*   Updated: 2026/02/14 11:35:13 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

// X軸まわりの回転 (pitch)
t_vec3	vec3_rotate_x(t_vec3 v, double angle)
{
	t_vec3	res;
	double	c = cos(angle);
	double	s = sin(angle);

	res.x = v.x;
	res.y = v.y * c - v.z * s;
	res.z = v.y * s + v.z * c;
	return (res);
}

// Y軸まわりの回転 (yaw)
t_vec3	vec3_rotate_y(t_vec3 v, double angle)
{
	t_vec3	res;
	double	c = cos(angle);
	double	s = sin(angle);

	res.x = v.x * c + v.z * s;
	res.y = v.y;
	res.z = -v.x * s + v.z * c;
	return (res);
}

// Z軸まわりの回転 (roll)
t_vec3	vec3_rotate_z(t_vec3 v, double angle)
{
	t_vec3	res;
	double	c = cos(angle);
	double	s = sin(angle);

	res.x = v.x * c - v.y * s;
	res.y = v.x * s + v.y * c;
	res.z = v.z;
	return (res);
}

// ロドリゲスの回転公式:
// V_rot = V*cos(theta) + (Axis x V)*sin(theta) + Axis*(Axis・V)*(1 - cos(theta))
t_vec3	vec3_rotate_axis(t_vec3 v, t_vec3 axis, double angle)
{
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	//axis = vec3_normalize(axis);

	// 第1項: V * cos(theta)
	term1 = vec3_scale(v, c);
	// 第2項: (Axis x V) * sin(theta)
	term2 = vec3_scale(vec3_cross(axis, v), s);
	// 第3項: Axis * (Axis ・ V) * (1 - cos(theta))
	term3 = vec3_scale(axis, vec3_dot(axis, v) * (1.0 - c));
	// 全て足し合わせる: term1 + term2 + term3
	return (vec3_add(vec3_add(term1, term2), term3));
}
