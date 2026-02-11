/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/11 10:21:43 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void object_control(int keycode, t_object *obj);
void camera_control(int keycode, t_camera *cam);

int	key_hook(int keycode, t_scene *scene)
{
	if (scene->selected_obj)
		object_control(keycode, scene->selected_obj);
	else
		camera_control(keycode, scene->cam);

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

		if ( scene->selected_obj)
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

void camera_control(int keycode, t_camera *cam)
{
	double move_speed = 1.0;
	double rot_speed = 0.05;

	// 移動 前後
	// Wキー：dir（向いている方向）に進む
	if (keycode == XK_w)
		cam->pos = vec3_add(cam->pos, vec3_scale(cam->dir, move_speed));
	// Sキー：dirの逆方向に進む
	if (keycode == XK_s)
		cam->pos = vec3_sub(cam->pos, vec3_scale(cam->dir, move_speed));
	// Dキー：right（右方向）に進む
	if (keycode == XK_d)
		cam->pos = vec3_add(cam->pos, vec3_scale(cam->right, move_speed));
	// Aキー：rightの逆方向に進む
	if (keycode == XK_a)
		cam->pos = vec3_sub(cam->pos, vec3_scale(cam->right, move_speed));
	// 移動 上下
	if (keycode == XK_q)
		cam->pos.y += move_speed;
    if (keycode == XK_z)
		cam->pos.y -= move_speed;
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
	// // debug
	// printf("pos: %f, %f, %f | dir: %f, %f, %f\n",
	// scene->cam->pos.x, scene->cam->pos.y, scene->cam->pos.z,
	// scene->cam->dir.x, scene->cam->dir.y, scene->cam->dir.z);
	// printf("dir: %f, %f, %f | right: %f, %f, %f\n",
    //     scene->cam->dir.x, scene->cam->dir.y, scene->cam->dir.z,
    //     scene->cam->right.x, scene->cam->right.y, scene->cam->right.z);
}

void object_control(int keycode, t_object *obj)
{
	double	move_step;
	// double 	rot_step;
	// t_vec3	*axis;

	// rot_step = 0.1;
	move_step = 1.0;
	if (keycode == XK_w)
		obj->pos.z += move_step;
    if (keycode == XK_s)
		obj->pos.z -= move_step;
    if (keycode == XK_d)
		obj->pos.x += move_step;
    if (keycode == XK_a)
		obj->pos.x -= move_step;
    if (keycode == XK_q)
		obj->pos.y += move_step;
    if (keycode == XK_z)
		obj->pos.y -= move_step;
}
