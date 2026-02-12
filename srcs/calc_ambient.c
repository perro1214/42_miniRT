/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:25:16 by hayato            #+#    #+#             */
/*   Updated: 2026/01/16 14:06:29 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
Ra = Ia × Ka

Ra: 環境光の反射輝度
Ia: 環境光の強度（シーン設定から）
Ka: 環境反射係数（今回は1として省略）
*/

// calc_ambient: アンビエントライトの影響を計算する
t_vec3	calc_ambient(t_ambient ambient, t_vec3 object_color)
{
	t_vec3	ambient_light;

	// Ra = Ia × Ka
	ambient_light = vec3_multiply(object_color, ambient.color);
	ambient_light = vec3_scale(ambient_light, ambient.ratio);
	return (ambient_light);
}
