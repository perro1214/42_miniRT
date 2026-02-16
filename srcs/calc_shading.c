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
	t_vec3	diffuse_color;
	t_vec3	specular_color;
	t_vec3	result;
	t_light	*curr_light;

	/* 環境光を計算（影の中でも適用される基本の明るさ） */
	result = calc_ambient(*ambient, rec->color);
	// ライトのリストを加算
	curr_light = light;
	while (curr_light)
	{
		/* 影の中かどうか判定 影になってない場合*/
		if (!is_in_shadow(objects, curr_light, rec->point, rec->normal))
		{
			/* 拡散反射光を計算 */
			diffuse_color = calc_diffuse(*curr_light, rec->point,
					rec->normal, rec->color);
			/* 鏡面反射光を計算 */
			specular_color = calc_specular(*curr_light, rec->point,
					rec->normal, rec->view_dir);
			/* 環境光 + 拡散反射光 + 鏡面反射光 */
			result = vec3_add(result, vec3_add(diffuse_color, specular_color));
		}
		// 影の場合はなにもしない。
		curr_light = curr_light->next;
	}
	/* 0-1 の範囲にクランプ */
	result = clamp_color(result);
	/* 0-1 → 0-255 に戻す */
	return (denormalize_color(result));
}
