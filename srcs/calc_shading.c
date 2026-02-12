/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:59:54 by hayato            #+#    #+#             */
/*   Updated: 2026/01/16 17:59:54 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** シェーディング計算（Phongモデル: 環境光 + 拡散反射）
**
** rec: 交差情報（colorは0-1に正規化済み）
** ambient: 環境光（colorは0-1に正規化済み）
** light: 光源（colorは0-1に正規化済み）
** 戻り値: 最終色（0-255）
*/
t_vec3	calc_shading(t_hit_record *rec, t_ambient *ambient, t_light *light)
{
	t_vec3	result;

	/* 環境光を計算（影の中でも適用される基本の明るさ） */
	result = calc_ambient(*ambient, rec->color);
	/* 拡散反射を計算して加算（光が当たる面の明るさ） */
	result = vec3_add(result, calc_diffuse(*light, rec->point, rec->normal,
				rec->color));
	/* 0-1 の範囲にクランプ（オーバーフロー防止） */
	result = clamp_color(result);
	/* 0-1 → 0-255 に戻す */
	return (denormalize_color(result));
}

/*
** ライティング計算（影の判定を含む）
**
** objects: シーン内の全オブジェクト（影判定用）
** ambient: 環境光
** light: 光源
** rec: 交差情報（colorは0-1に正規化済み）
** 戻り値: 最終色（0-255）
*/
t_vec3	calc_lighting(t_object *objects, t_ambient *ambient,
		t_light *light, t_hit_record *rec)
{
	t_vec3	ambient_color;
	t_vec3	diffuse_color;
	t_vec3	result;

	/* 環境光を計算（影の中でも適用される基本の明るさ） */
	ambient_color = calc_ambient(*ambient, rec->color);
	/* 影の中かどうか判定 */
	if (is_in_shadow(objects, light, rec->point, rec->normal))
	{
		/* 影の中は環境光のみ */
		result = clamp_color(ambient_color);
		return (denormalize_color(result));
	}
	/* 拡散反射光を計算 */
	diffuse_color = calc_diffuse(*light, rec->point, rec->normal, rec->color);
	/* 環境光 + 拡散反射光 */
	result = vec3_add(ambient_color, diffuse_color);
	/* 0-1 の範囲にクランプ */
	result = clamp_color(result);
	/* 0-1 → 0-255 に戻す */
	return (denormalize_color(result));
}
