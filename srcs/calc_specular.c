/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_specular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 00:00:00 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/16 00:00:00 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Rs = Ks × Ii × (R · V)^n

Rs: 鏡面反射光の輝度
Ks: 鏡面反射係数（SPECULAR_COEFF）
Ii: 入射光の強度
R: 反射ベクトル = 2(N · L)N - L
V: 視線方向ベクトル（交点→カメラ、正規化済み）
n: 光沢度（SHININESS）
*/

// vec3_reflect: 入射ベクトルを法線で反射する
// reflect(L, N) = 2(N · L)N - L
static t_vec3	vec3_reflect(t_vec3 light_dir, t_vec3 normal)
{
	double	n_dot_l;

	n_dot_l = vec3_dot(normal, light_dir);
	return (vec3_sub(vec3_scale(normal, 2.0 * n_dot_l), light_dir));
}

// calc_specular: 鏡面反射光の影響を計算する
t_vec3	calc_specular(t_light light, t_vec3 hit_point,
		t_vec3 normal, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	double	r_dot_v;
	double	spec;

	// 光源方向ベクトルの計算（交点から光源へのベクトル）
	light_dir = vec3_normalize(vec3_sub(light.curr.pos, hit_point));
	// 反射ベクトルの計算
	reflect_dir = vec3_reflect(light_dir, normal);
	// 反射ベクトルと視線方向の内積
	r_dot_v = vec3_dot(reflect_dir, view_dir);
	// 内積が負の場合、鏡面反射は見えない
	if (r_dot_v < 0)
		return (vec3_init(0, 0, 0));
	// Rs = Ks × Ii × Il × (R · V)^n
	spec = SPECULAR_COEFF * light.intensity * pow(r_dot_v, SHININESS);
	return (vec3_scale(light.color, spec));
}
