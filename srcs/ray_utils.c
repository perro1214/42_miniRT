/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:29:02 by hayato            #+#    #+#             */
/*   Updated: 2026/02/16 23:49:28 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	ray_init(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = vec3_normalize(direction);
	return (ray);
}

t_vec3	ray_at(t_ray ray, double t)
{
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}
