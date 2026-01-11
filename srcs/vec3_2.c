/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:18:58 by hayato            #+#    #+#             */
/*   Updated: 2026/01/11 18:19:18 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3_init(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y
			- a.y * b.x));
}

double	vec3_norm(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	norm;

	norm = vec3_norm(v);
	if (norm == 0)
	{
		return (vec3_init(0, 0, 0)); // 正規化できない場合はゼロベクトルを返す
	}
	return (vec3_scale(v, 1.0 / norm));
}
