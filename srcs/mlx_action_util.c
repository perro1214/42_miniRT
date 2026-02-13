/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/12 18:18:49 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	update_object_rotation(t_object *obj);
void	update_camera(t_camera *cam);

/**
 * @brief Move the target.
 *
 * @param keycode
 * @param scene
 */
void	move_control(int keycode, t_scene *scene)
{
	t_transform *target;
	t_vec3		dir;
	double		move_speed;

	move_speed = 1.0;
	if (scene->mode == OBJECT && scene->selected_obj)
		target = &scene->selected_obj->curr;
	else if (scene->mode == LIGHT && scene->selected_lig)
		target = &scene->selected_lig->curr;
	else if (scene->mode == CAMERA)
		target = &scene->cam->curr;
	else
	{
		return ;
	}
	dir = get_move_direction(keycode, scene->cam);
	if (vec3_dot(dir, dir) > EPSILON)
	{
		target->pos = vec3_add(target->pos, vec3_scale(dir, move_speed));
		if (target == &scene->cam->curr)
			update_camera(scene->cam);
		render_scene(scene);
	}
}

/**
 * @brief Rotate the target.
 *
 * @param keycode
 * @param scene
 */
void	rotate_control(int keycode, t_scene *scene)
{
	t_transform *target;
    double      rot_step;
	int 		changed;

	rot_step = 0.05;
	changed = 0;
	if (scene->mode == LIGHT)
		return ;
    if (scene->mode == OBJECT && scene->selected_obj)
        target = &scene->selected_obj->curr;
    else if (scene->mode == CAMERA)
        target = &scene->cam->curr;
    else
	{
        return;
	}
	if (keycode == XK_i || keycode == XK_k || keycode == XK_l || keycode ==XK_j)
		changed = 1;
	if (keycode == XK_i)
		target->angle.x += rot_step;
    if (keycode == XK_k)
		target->angle.x -= rot_step;
    if (keycode == XK_l)
		target->angle.y += rot_step;
    if (keycode == XK_j)
		target->angle.y -= rot_step;
	if(!changed)
		return ;
    if (scene->mode == OBJECT)
        update_object_rotation(scene->selected_obj);
    else
        update_camera(scene->cam);
    render_scene(scene);
}

void	update_object_rotation(t_object *obj)
{
	t_vec3	base_normal;
	t_vec3	rot_dir;

	if (obj->type == PLANE)
        base_normal = obj->data.pl.normal;
    else if (obj->type == CYLINDER)
        base_normal = obj->data.cy.normal;
    else
	{
        return ;
	}
	rot_dir = vec3_rotate_x(base_normal, obj->curr.angle.x);
	rot_dir = vec3_rotate_y(rot_dir, obj->curr.angle.y);
	rot_dir = vec3_rotate_z(rot_dir, obj->curr.angle.z);
	obj->curr.normal = vec3_normalize(rot_dir);
}

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

/**
 * @brief Reset values of the target.
 *
 * @param keycode
 * @param scene
 */
void reset_control(int keycode, t_scene *scene)
{
	if(keycode != XK_r)
		return;
	if (scene->mode == OBJECT && scene->selected_obj)
	{
		scene->selected_obj->curr.pos = scene->selected_obj->pos;
		scene->selected_obj->curr.angle = vec3_init(0, 0, 0);
		if (scene->selected_obj->type == PLANE)
			scene->selected_obj->curr.normal = scene->selected_obj->data.pl.normal;
		else if (scene->selected_obj->type == CYLINDER)
			scene->selected_obj->curr.normal = scene->selected_obj->data.cy.normal;
		else
			scene->selected_obj->curr.normal = vec3_init(0, 0, 0);
		update_object_rotation(scene->selected_obj);
	}
	else if (scene->mode == LIGHT && scene->selected_lig)
		scene->selected_lig->curr.pos = scene->selected_lig->pos;
	else if (scene->mode == CAMERA)
	{
		scene->cam->curr.pos = scene->cam->pos;
		scene->cam->curr.normal = vec3_normalize(scene->cam->dir);
		scene->cam->curr.angle = vec3_init(0, 0, 0);
		update_camera(scene->cam);
	}
	render_scene(scene);
}
