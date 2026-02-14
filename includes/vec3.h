/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 18:29:29 by hayato            #+#    #+#             */
/*   Updated: 2026/02/14 11:14:03 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

t_vec3	vec3_init(float x, float y, float z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, float scalar);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_norm(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_vec3	vec3_multiply(t_vec3 a, t_vec3 b);
t_vec3	vec3_rotate_x(t_vec3 v, double angle);
t_vec3	vec3_rotate_y(t_vec3 v, double angle);
t_vec3	vec3_rotate_z(t_vec3 v, double angle);
t_vec3	vec3_rotate_axis(t_vec3 v, t_vec3 axis, double angle);
// void vec3_print(t_vec3 v); //  debug

#endif // VEC3_H
