/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:33:35 by hayato            #+#    #+#             */
/*   Updated: 2026/02/11 22:46:51 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// カメラを移動したときにレイを飛ばすための基底ベクトルを計算、更新する。
// 1.現在の角度からdirを計算 -> 完了
// 2.init_dir(正規化済みに対して、回転を適用 -> 完了
// ->球座標にする方法もある。
// 3.ワールド座標の上を定義する ->完了
// 4.right(右方向の計算） 真上とカメラの上の向きの外積 ->完了
// 5.カメラが真上を向くと外積が0になるので対策必要 -> 完了
// 6.カメラのup上の計算：向きと方向向の外積 ->完了
void	update_camera(t_camera *cam)
{
	t_vec3	world_up;
	t_vec3	rot_dir;

	rot_dir = vec3_rotate_x(cam->dir,cam->curr.angle.x);
	rot_dir = vec3_rotate_y(rot_dir,cam->curr.angle.y);
	cam->curr.normal = vec3_normalize(rot_dir);
	world_up = vec3_init(0, 1, 0);
	if (fabs(vec3_dot(cam->curr.normal, world_up)) > 0.9999)
		world_up = vec3_init(0, 0, 1);
	// 右ベクトル = world_up × 視線方向
	cam->right = vec3_normalize(vec3_cross(world_up, cam->curr.normal));
	// 上ベクトル = 視線方向 × 右ベクトル
	cam->up = vec3_normalize(vec3_cross(cam->curr.normal, cam->right));
}
