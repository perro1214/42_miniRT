/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:27:35 by hayato            #+#    #+#             */
/*   Updated: 2026/02/10 17:36:23 by htsutsum         ###   ########.fr       */
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
