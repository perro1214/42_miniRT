/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:25:16 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 16:29:31 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	calc_ambient(t_ambient ambient, t_vec3 object_color)
{
	t_vec3	ambient_light;

	ambient_light = vec3_multiply(object_color, ambient.color);
	ambient_light = vec3_scale(ambient_light, ambient.ratio);
	return (ambient_light);
}
