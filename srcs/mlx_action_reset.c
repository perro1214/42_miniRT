/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_reset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 02:02:39 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Reset values of the target.
 *
 * @param keycode
 * @param scene
 */
void	reset_control(t_scene *scene)
{
	t_object	*obj;

	obj = scene->selected_obj;
	if (scene->mode == OBJECT && obj)
	{
		obj->curr.pos = obj->pos;
		obj->curr.angle = vec3_init(0, 0, 0);
		if (obj->type == PLANE)
			obj->curr.normal = obj->data.pl.normal;
		else if (obj->type == CYLINDER)
			obj->curr.normal = obj->data.cy.normal;
		else if (obj->type == CONE)
			obj->curr.normal = obj->data.co.normal;
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
