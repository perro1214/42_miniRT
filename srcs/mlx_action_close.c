/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/11 09:36:37 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	key_hook(int keycode, t_scene *scene)
{
	double move_speed = 1.0;
	double rot_speed = 0.05;

	// 移動 前後
	// Wキー：dir（向いている方向）に進む
	if (keycode == XK_w)
		scene->cam->pos = vec3_add(scene->cam->pos, vec3_scale(scene->cam->dir, move_speed));
	// Sキー：dirの逆方向に進む
	if (keycode == XK_s)
		scene->cam->pos = vec3_sub(scene->cam->pos, vec3_scale(scene->cam->dir, move_speed));
	// Dキー：right（右方向）に進む
	if (keycode == XK_d)
		scene->cam->pos = vec3_add(scene->cam->pos, vec3_scale(scene->cam->right, move_speed));
	// Aキー：rightの逆方向に進む
	if (keycode == XK_a)
		scene->cam->pos = vec3_sub(scene->cam->pos, vec3_scale(scene->cam->right, move_speed));
	// 移動 上下
	if (keycode == XK_q)
		scene->cam->pos.y += move_speed;
    if (keycode == XK_z)
		scene->cam->pos.y -= move_speed;
	// 回転
	if (keycode == XK_i)
		scene->cam->pitch += rot_speed;
    if (keycode == XK_k)
		scene->cam->pitch -= rot_speed;
    if (keycode == XK_j)
		scene->cam->yaw -= rot_speed;
    if (keycode == XK_l)
		scene->cam->yaw += rot_speed;
	// リセット
	if (keycode == XK_r)
	{
		scene->cam->pos = scene->cam->init_pos;
		scene->cam->pitch = 0.0;
		scene->cam->yaw = 0.0;
	}
	if (keycode == XK_Escape)
		close_window(scene);

	update_camera(scene->cam);
	render_scene(scene);

	// // debug
	// printf("pos: %f, %f, %f | dir: %f, %f, %f\n",
	// scene->cam->pos.x, scene->cam->pos.y, scene->cam->pos.z,
	// scene->cam->dir.x, scene->cam->dir.y, scene->cam->dir.z);
	// printf("dir: %f, %f, %f | right: %f, %f, %f\n",
    //     scene->cam->dir.x, scene->cam->dir.y, scene->cam->dir.z,
    //     scene->cam->right.x, scene->cam->right.y, scene->cam->right.z);
	return (0);
}

// ウィンドウの大きさ変更したときも、レンダリングする。レンダリングの大きさは変更しない。
int	expose_hook(t_scene *scene)
{
	render_scene(scene);
	return (0);
}


//
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
