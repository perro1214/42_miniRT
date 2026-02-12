/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_diffuse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:50:13 by hayato            #+#    #+#             */
/*   Updated: 2026/02/12 18:40:50 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Rd = Kd × Ii × (N · L)

Rd: 拡散反射光の輝度
Kd: 拡散反射係数（物体の色）
Ii: 入射光の強度
N: 法線ベクトル（正規化済み）
L: 光源方向ベクトル（交点→光源、正規化済み）
*/

// calc_diffuse: 拡散反射光の影響を計算する

t_vec3	calc_diffuse(t_light light, t_vec3 hit_point, t_vec3 normal,
		t_vec3 object_color)
{
	t_vec3	light_dir;
	double	N_dot_L;
	t_vec3	diffuse_light;

	// 光源方向ベクトルの計算（交点から光源へのベクトル）
	light_dir = vec3_normalize(vec3_sub(light.curr.pos, hit_point));
	// 法線ベクトルと光源方向ベクトルの内積を計算
	N_dot_L = vec3_dot(normal, light_dir);
	// 内積が負の場合、光源は表面の裏側にあるため、拡散光は0
	if (N_dot_L < 0)
		N_dot_L = 0;
	// Rd = Kd × Il × Ii × (N · L)
	// Kd: オブジェクト色, Il: 光源色, Ii: 光の強度
	diffuse_light = vec3_multiply(object_color, light.color);
	diffuse_light = vec3_scale(diffuse_light, light.intensity * N_dot_L);
	return (diffuse_light);
}
