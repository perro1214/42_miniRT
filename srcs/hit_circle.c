/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_circle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:01:13 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/10 01:56:19 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	hit_circle(t_object *obj, t_ray ray)
{
		t_vec3	center;
		t_vec3	n;
		double	r;

		center = obj->position;
		n = obj->data.ci.normal;
		r = obj->data.ci.radius;
		return (hit_disk(ray, center, n, r));
}

