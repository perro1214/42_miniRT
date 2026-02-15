/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/15 05:40:27 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	selected_target(int keycode, t_scene *scene);
static void	switch_light(t_scene *scene);

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == XK_Escape)
		close_window(scene);
	if (keycode == XK_space || keycode == XK_Tab)
		selected_target(keycode, scene);
	if (keycode == XK_w || keycode == XK_s || keycode == XK_a || keycode == XK_d || keycode == XK_q || keycode == XK_z)
		move_control(keycode, scene);
	if (keycode == XK_i || keycode == XK_k || keycode == XK_l || keycode ==XK_j)
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
	{
		ft_putstr_fd("Selected : Light ", 1);
		ft_putstr_fd("[",1);
		ft_putstr_fd(ft_itoa(scene->selected_lig->id), 1);
		ft_putendl_fd("]", 1);
	}
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
