/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/16 23:48:36 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	rotate_object(int keycode, t_scene *scene)
{
	t_object	*obj;
	t_vec3		axis;
	double		angle;
	double		rot_step;
	double		half_h;
	t_vec3		mid;

	obj = scene->selected_obj;
	rot_step = 0.1;
	if (keycode == XK_i)
	{
		axis = scene->cam->right;
		angle = rot_step;
	}
	else if (keycode == XK_k)
	{
		axis = scene->cam->right;
		angle = -rot_step;
	}
	else if (keycode == XK_l || keycode == XK_j)
	{
		axis = scene->cam->curr.normal;
		if (keycode == XK_l)
			angle = -rot_step;
		else
			angle = rot_step;
	}
	else
		return ;
	if (obj->type == CYLINDER || obj->type == CONE)
	{
		if (obj->type == CYLINDER)
			half_h = obj->data.cy.half_h;
		else if (obj->type == CONE)
			half_h = obj->data.co.half_h;
		mid = vec3_add(obj->curr.pos, vec3_scale(obj->curr.normal, half_h));
		obj->curr.normal = vec3_rotate_axis(obj->curr.normal, axis, angle);
		obj->curr.normal = vec3_normalize(obj->curr.normal);
		obj->right = vec3_normalize(vec3_rotate_axis(obj->right, axis, angle));
		obj->up = vec3_normalize(vec3_rotate_axis(obj->up, axis, angle));
		obj->curr.pos = vec3_sub(mid, vec3_scale(obj->curr.normal, half_h));
	}
	else
	{
		obj->curr.normal = vec3_rotate_axis(obj->curr.normal, axis, angle);
		obj->curr.normal = vec3_normalize(obj->curr.normal);
		obj->right = vec3_normalize(vec3_rotate_axis(obj->right, axis, angle));
		obj->up = vec3_normalize(vec3_rotate_axis(obj->up, axis, angle));
	}
}

void	rotate_camera_b(int keycode, t_scene *scene)
{
	t_camera	*cam;
	t_vec3		axis;
	double		angle;
	double		step;

	cam = scene->cam;
	step = 0.1;
	if (keycode == XK_i || keycode == XK_k)
	{
		axis = cam->right;
		if (keycode == XK_i)
			angle = -step;
		else
			angle = step;
		cam->curr.normal = vec3_rotate_axis(cam->curr.normal, axis, angle);
		cam->up = vec3_rotate_axis(cam->up, axis, angle);
	}
	else if (keycode == XK_l || keycode == XK_j)
	{
		axis = vec3_init(0, 1, 0);
		if (keycode == XK_l)
			angle = step;
		else
			angle = -step;
		cam->curr.normal = vec3_rotate_axis(cam->curr.normal, axis, angle);
		cam->right = vec3_rotate_axis(cam->right, axis, angle);
		cam->up = vec3_rotate_axis(cam->up, axis, angle);
	}
	else
		return ;
	cam->curr.normal = vec3_normalize(cam->curr.normal);
	cam->right = vec3_normalize(vec3_cross(cam->up, cam->curr.normal));
	cam->up = vec3_normalize(vec3_cross(cam->curr.normal, cam->right));
}

/**
 * @brief Move the target.
 *
 * @param keycode
 * @param scene
 */
void	move_control(int keycode, t_scene *scene)
{
	t_transform	*target;
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
		scene->render_flag = 1;
	}
}

void	rotate_control(int keycode, t_scene *scene)
{
	if (scene->mode == CAMERA)
	{
		rotate_camera_b(keycode, scene);
		scene->render_flag = 1;
	}
	else if (scene->mode == OBJECT && scene->selected_obj)
	{
		if (scene->selected_obj->type == CYLINDER
			|| scene->selected_obj->type == PLANE
			|| scene->selected_obj->type == CONE)
		{
			rotate_object(keycode, scene);
			scene->render_flag = 1;
		}
	}
}

void	update_camera(t_camera *cam)
{
	t_vec3	world_up;
	t_vec3	rot_dir;

	rot_dir = vec3_rotate_x(cam->dir, cam->curr.angle.x);
	rot_dir = vec3_rotate_y(rot_dir, cam->curr.angle.y);
	cam->curr.normal = vec3_normalize(rot_dir);
	world_up = vec3_init(0, 1, 0);
	if (fabs(vec3_dot(cam->curr.normal, world_up)) > 0.9999)
		world_up = vec3_init(0, 0, 1);
	cam->right = vec3_normalize(vec3_cross(world_up, cam->curr.normal));
	cam->up = vec3_normalize(vec3_cross(cam->curr.normal, cam->right));
}

/**
 * @brief Reset values of the target.
 *
 * @param keycode
 * @param scene
 */
void	reset_control(int keycode, t_scene *scene)
{
	if (keycode != XK_r)
		return ;
	if (scene->mode == OBJECT && scene->selected_obj)
	{
		scene->selected_obj->curr.pos = scene->selected_obj->pos;
		scene->selected_obj->curr.angle = vec3_init(0, 0, 0);
		if (scene->selected_obj->type == PLANE)
			scene->selected_obj->curr.normal = scene->selected_obj->data.pl.normal;
		else if (scene->selected_obj->type == CYLINDER)
			scene->selected_obj->curr.normal = scene->selected_obj->data.cy.normal;
		else if (scene->selected_obj->type == CONE)
			scene->selected_obj->curr.normal = scene->selected_obj->data.co.normal;
		else
			scene->selected_obj->curr.normal = vec3_init(0, 0, 0);
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
	scene->render_flag = 1;
}
