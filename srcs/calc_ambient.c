/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayato <hayato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 13:25:16 by hayato            #+#    #+#             */
/*   Updated: 2026/01/16 13:27:39 by hayato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// 色の範囲を0-255にクランプするヘルパー関数
static float	clamp_color(float value)
{
	if (value > 255.0f)
		return (255.0f);
	if (value < 0.0f)
		return (0.0f);
	return (value);
}

// calc_ambient: アンビエントライトの影響を計算する
t_vec3	calc_ambient(t_ambient ambient, t_vec3 object_color)
{
	t_vec3	result_color;

	result_color.x = object_color.x * ambient.ratio * (ambient.color.x / 255.0f);
	result_color.y = object_color.y * ambient.ratio * (ambient.color.y / 255.0f);
	result_color.z = object_color.z * ambient.ratio * (ambient.color.z / 255.0f);
	// 色の範囲を0-255にクランプ
	result_color.x = clamp_color(result_color.x);
	result_color.y = clamp_color(result_color.y);
	result_color.z = clamp_color(result_color.z);
	return (result_color);
}
