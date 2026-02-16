/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_move.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 02:05:35 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

/**
 * @brief Get the move direction.
 *
 * @param keycode
 * @param cam
 * @return t_vec3
 */
t_vec3	get_move_direction(int keycode, t_camera *cam)
{
	if (keycode == XK_w)
		return (cam->curr.normal);
	if (keycode == XK_s)
		return (vec3_scale(cam->curr.normal, -1.0));
	if (keycode == XK_d)
		return (cam->right);
	if (keycode == XK_a)
		return (vec3_scale(cam->right, -1.0));
	if (keycode == XK_q)
		return (vec3_init(0, 1.0, 0));
	if (keycode == XK_z)
		return (vec3_init(0, -1.0, 0));
	return (vec3_init(0, 0, 0));
}
