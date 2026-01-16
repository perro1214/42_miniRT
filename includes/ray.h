/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:27:35 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 21:16:51 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_vec3	origin;// S
	t_vec3	direction;// D
}			t_ray;

t_ray	ray_init(t_vec3 origin, t_vec3 direction);
t_vec3	ray_at(t_ray ray, double t);

#endif // RAY_H
