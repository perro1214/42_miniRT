/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:29:25 by hayato            #+#    #+#             */
/*   Updated: 2026/01/16 22:36:14 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	screen_x_corrected(int px, double aspect_ratio)
{
	return ((2.0 * px / (WIN_WIDTH - 1) - 1.0) * aspect_ratio);
}

static double	screen_y_corrected(int py, double aspect_ratio)
{
	(void)aspect_ratio;
	return (1.0 - 2.0 * py / (WIN_HEIGHT - 1));
}

/*
固定カメラ　テスト

スクリーンの座標を[-1,1]に正規化し、カメラの位置と方向を基にレイを生成する関数
位置(0,0,-5)
方向(0,0,1)
スクリーン位置 z=0
*/
t_ray	get_ray_fixed(int px, int py)
{
	t_vec3 camera_pos;   // カメラ位置
	t_vec3 screen_point; // スクリーン上の点
	t_vec3 direction;    // レイの方向
	double aspect_ratio; // アスペクト比
	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	camera_pos = vec3_init(0.0, 0.0, -5.0);
	screen_point = vec3_init(screen_x_corrected(px, aspect_ratio),
			screen_y_corrected(py, aspect_ratio), 0.0);
	direction = vec3_sub(screen_point, camera_pos);
	return (ray_init(camera_pos, direction));
}
