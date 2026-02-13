/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/12 18:13:06 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	selected_target(int keycode, t_scene *scene);
static void	switch_light(t_scene *scene);

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == XK_Escape)
		close_window(scene);
	selected_target(keycode, scene);
	move_control(keycode, scene);
	rotate_control(keycode, scene);
	if (keycode == XK_r)
		reset_control(keycode, scene);
	return (0);
}

/**
 * @brief Select the target.
 *
 * @param keycode
 * @param scene
 * @return void
 */
static void	selected_target(int keycode, t_scene *scene)
{
	if (keycode == XK_space)
	{
		scene->mode = CAMERA;
		ft_putendl_fd("Selected : CAMERA (Home)", 1);
	}
	else if (keycode == XK_Tab)
	{
		scene->mode = LIGHT;
		switch_light(scene);
	}
}

/**
 * @brief Switch the light.
 *
 * @param scene
 */
static void	switch_light(t_scene *scene)
{
	if (scene->selected_lig == NULL || scene->selected_lig->next == NULL)
		scene->selected_lig = scene->ligs;
	else
		scene->selected_lig = scene->selected_lig->next;

	if(scene->selected_lig)
		ft_putendl_fd("Selected : Light", 1);
}

/**
 * @brief Get the move direction.
 *
 * @param keycode
 * @param cam
 * @return t_vec3
 */
t_vec3 get_move_direction(int keycode, t_camera *cam)
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
