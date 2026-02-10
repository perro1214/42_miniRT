/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:18:58 by hayato            #+#    #+#             */
/*   Updated: 2026/02/10 04:41:25 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

// X軸まわりの回転 (ピッチ)
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

// Y軸まわりの回転 (ヨー)
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

// Z軸まわりの回転 (ロール)
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
