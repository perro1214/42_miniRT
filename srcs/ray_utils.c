/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:29:02 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 21:29:19 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

// レイの生成
t_ray	ray_init(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec3_normalize(direction);
	return (ray);
}

// レイ上の点を取得 P = S + t * D
t_vec3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}
