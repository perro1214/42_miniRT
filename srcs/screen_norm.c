/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:29:25 by hayato            #+#    #+#             */
/*   Updated: 2026/02/13 20:09:21 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	clamp_tan_fov(double fov);

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
// スクリーン位置 z=0
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

// get_ray
// t_camera 引数追加 ->完了
// fovとアスペクト比からスケーを計算 -> 完了
// ワールド座標(0 - WIN_WIDTH)を -1.0 ～ 1.0の範囲に正規化、中心を0.0にし、アスペクト比とスケールを掛ける
// カメラの基底ベクトル (dir ,right, up)を使って方向合成
// 方向 = (前方向 * 1.0) + (右方向 * x_n) + (上方向 * y_n);
// 最後に真っすぐなベクトルに upとrightを足すことで、上下左右の移動が可能になる。
t_ray	get_ray(int px, int py, t_camera *cam)
{
	double	x_n;
	double	y_n;
	t_vec3	ray_dir;

	x_n = (2.0 * (px + 0.5) * cam->inv_width - 1.0)
          * cam->aspect_ratio * cam->render_scale;
    y_n = (1.0 - 2.0 * (py + 0.5) * cam->inv_height)
          * cam->render_scale;
	ray_dir = vec3_add(cam->curr.normal, vec3_add(vec3_scale(cam->right, x_n), vec3_scale(cam->up, y_n)));
	return (ray_init(cam->curr.pos, ray_dir));
}

void init_camera_constant(t_camera *cam)
{
    cam->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
    cam->render_scale = tan((clamp_tan_fov(cam->fov) * M_PI / 180.0) * 0.5);
    cam->inv_width = 1.0 / (double)WIN_WIDTH;
    cam->inv_height = 1.0 / (double)WIN_HEIGHT;
}

static double	clamp_tan_fov(double fov)
{
	if ( fov == 0)
		return (EPSILON);
	else if ( fov == 180)
		return (180-EPSILON);
	else
		return (fov);
}
