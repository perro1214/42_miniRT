/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 21:32:26 by hayato            #+#    #+#             */
/*   Updated: 2026/01/13 22:27:09 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// 判別式を計算する関数(oc = 球の中心からレイの原点へのベクトル、ray = レイ、radius = 球の半径)
//
static double	calculate_discriminant(t_vec3 oc, t_ray ray, double radius)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	// 二次方程式の係数を計算
	// A = D · D (方向ベクトルが正規化されていれば 1)
	a = vec3_dot(ray.direction, ray.direction);
	// B = 2 × (S-C) · D
	b = 2.0 * vec3_dot(oc, ray.direction);
	// C = (S-C) · (S-C) - r^2
	c = vec3_dot(oc, oc) - radius * radius;
	// 判別式を計算
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1.0);
	return (discriminant);
}
// 　tを計算(t_vec3 oc, t_ray ray, double radius,double discriminant)

static double	calculate_t(t_vec3 oc, t_ray ray, double dis)
{
	double	t1;
	double	t2;
	double	a;
	double	b;

	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0 * vec3_dot(oc, ray.direction);
	t1 = (-b - sqrt(dis)) / (2.0 * a);
	t2 = (-b + sqrt(dis)) / (2.0 * a);
	if (t1 >= 0.0001)
	{
		return (t1);
	}
	else if (t2 >= 0.0001)
	{
		return (t2);
	}
	else
	{
		return (-1.0);
	}
}

// 球とレイの交差判定を行う関数
double	hit_sphere(t_sphere *sphere, t_ray ray)
{
	double	discriminant;
	double	t;
	t_vec3	oc;

	// oc = S - C
	oc = vec3_sub(ray.origin, sphere->center);
	discriminant = calculate_discriminant(oc, ray, sphere->radius);
	// 交差なし
	if (discriminant < 0)
		return (-1.0);
	// 判別式が非負の場合、交点の t = (-B √D)/2A 値を計算
	t = calculate_t(oc, ray, discriminant);
	if (discriminant < 0)
		return (-1.0);
	return (t);
}
