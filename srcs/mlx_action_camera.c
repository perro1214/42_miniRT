/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/11 12:51:22 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void	object_control(int keycode, t_object *obj);
void	camera_control(int keycode, t_scene *scene);
void	object_rotation(int keycode, t_object *obj);
void	update_object_rotation(t_object *obj);

int	key_hook(int keycode, t_scene *scene)
{
	if (scene->selected_obj)
		object_control(keycode, scene->selected_obj);
	else
		camera_control(keycode, scene);

	if (keycode == XK_Escape)
		close_window(scene);

	update_camera(scene->cam);
	render_scene(scene);
	return (0);
}

// ウィンドウの大きさ変更したときも、レンダリングする。レンダリングの大きさは変更しない。
int	expose_hook(t_scene *scene)
{
	render_scene(scene);
	return (0);
}

// 左マウスクリックで動かすオブジェクトを選択
int mouse_hook(int button, int x, int y, t_scene *scene)
{
	double	t;
	t_ray	ray;

	if (button == 1)
	{
		ray = get_ray(x, y, scene->cam);
		scene->selected_obj = find_closest_obj(scene, ray, &t);
		if (scene->selected_obj)
			printf("Selected: %d at distance %f\n", scene->selected_obj->type, t);
		else
			printf("Selected cleared..\n");
		render_scene(scene);
	}
	return (0);
}

int	close_window(t_scene *scene)
{
	mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
	mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
	free(scene->mlx->mlx);
	free_scene(scene);
	exit(0);
	return (0);
}

// 移動可能距離を計算（オブジェクトとの衝突を考慮）
static double	get_safe_move_distance(t_scene *scene, t_vec3 move_dir,
					double requested_dist)
{
	t_ray	ray;
	double	hit_dist;
	double	safe_margin;

	safe_margin = 0.5;
	ray.origin = scene->cam->pos;
	ray.direction = vec3_normalize(move_dir);
	// オブジェクトとの交差判定
	find_closest_obj(scene, ray, &hit_dist);
	// 安全距離（オブジェクト手前にマージンを設ける）
	if (hit_dist < requested_dist + safe_margin)
		return (fmax(0.0, hit_dist - safe_margin));
	return (requested_dist);
}

// カメラを指定方向に安全に移動する
static void	move_camera_safe(t_scene *scene, t_vec3 move_dir, double speed)
{
	double	safe_dist;

	safe_dist = get_safe_move_distance(scene, move_dir, speed);
	if (safe_dist > 0.0)
		scene->cam->pos = vec3_add(scene->cam->pos,
				vec3_scale(vec3_normalize(move_dir), safe_dist));
}

void	camera_control(int keycode, t_scene *scene)
{
	t_camera	*cam;
	double		move_speed;
	double		rot_speed;

	cam = scene->cam;
	move_speed = 1.0;
	rot_speed = 0.05;
	// 移動 前後（衝突判定付き）
	if (keycode == XK_w)
		move_camera_safe(scene, cam->dir, move_speed);
	if (keycode == XK_s)
		move_camera_safe(scene, vec3_scale(cam->dir, -1), move_speed);
	// 移動 左右（衝突判定付き）
	if (keycode == XK_d)
		move_camera_safe(scene, cam->right, move_speed);
	if (keycode == XK_a)
		move_camera_safe(scene, vec3_scale(cam->right, -1), move_speed);
	// 移動 上下（衝突判定付き）
	if (keycode == XK_q)
		move_camera_safe(scene, vec3_init(0, 1, 0), move_speed);
	if (keycode == XK_z)
		move_camera_safe(scene, vec3_init(0, -1, 0), move_speed);
	// 回転
	if (keycode == XK_i)
		cam->pitch += rot_speed;
	if (keycode == XK_k)
		cam->pitch -= rot_speed;
	if (keycode == XK_j)
		cam->yaw -= rot_speed;
	if (keycode == XK_l)
		cam->yaw += rot_speed;
	// リセット
	if (keycode == XK_r)
	{
		cam->pos = cam->init_pos;
		cam->pitch = 0.0;
		cam->yaw = 0.0;
	}
}

void	object_control(int keycode, t_object *obj)
{
	double	move_step;

	move_step = 1.0;
	if (keycode == XK_w)
		obj->curr.pos.z += move_step;
	if (keycode == XK_s)
		obj->curr.pos.z -= move_step;
	if (keycode == XK_d)
		obj->curr.pos.x += move_step;
	if (keycode == XK_a)
		obj->curr.pos.x -= move_step;
	if (keycode == XK_q)
		obj->curr.pos.y += move_step;
	if (keycode == XK_z)
		obj->curr.pos.y -= move_step;
	object_rotation(keycode, obj);
}

void object_rotation(int keycode, t_object *obj)
{
	double rot_step;

	rot_step = 0.05;
	if (keycode == XK_i)
		obj->curr.angle.x += rot_step; // 上に傾く
    if (keycode == XK_k)
		obj->curr.angle.x -= rot_step; // 下に傾く
    if (keycode == XK_l)
		obj->curr.angle.y += rot_step; // 右に回る
    if (keycode == XK_j)
		obj->curr.angle.y -= rot_step; // 左に回る
	update_object_rotation(obj);
}

void update_object_rotation(t_object *obj)
{
	t_vec3	base_normal;
	t_vec3	dir_n;

	if (obj->type == PLANE)
        base_normal = obj->data.pl.normal;
    else if (obj->type == CYLINDER)
        base_normal = obj->data.cy.normal;
    else
	{
        return ;
	}
	dir_n = vec3_rotate_x(base_normal, obj->curr.angle.x);
	dir_n = vec3_rotate_y(dir_n, obj->curr.angle.y);
	dir_n = vec3_rotate_z(dir_n, obj->curr.angle.z);
	obj->curr.normal = vec3_normalize(dir_n);
}
