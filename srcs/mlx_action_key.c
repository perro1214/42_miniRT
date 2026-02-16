/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_key.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 02:23:22 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	selected_target(int keycode, t_scene *scene);
static void	switch_light(t_scene *scene);
static void	rotate_control(int keycode, t_scene *scene);

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == XK_Escape)
		close_window(scene);
	if (keycode == XK_space || keycode == XK_Tab)
		selected_target(keycode, scene);
	if (keycode == XK_w || keycode == XK_s || keycode == XK_a || keycode == XK_d
		|| keycode == XK_q || keycode == XK_z)
		move_control(keycode, scene);
	if (keycode == XK_i || keycode == XK_k || keycode == XK_l
		|| keycode == XK_j)
		rotate_control(keycode, scene);
	if (keycode == XK_r)
		reset_control(scene);
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
	if (scene->selected_lig)
	{
		ft_putstr_fd("Selected : Light ", 1);
		ft_putstr_fd("[", 1);
		ft_putstr_fd(ft_itoa(scene->selected_lig->id), 1);
		ft_putendl_fd("]", 1);
	}
}

/**
 * @brief Rotate the target
 *
 * @param keycode
 * @param scene
 */
void	rotate_control(int keycode, t_scene *scene)
{
	if (scene->mode == CAMERA)
	{
		rotate_camera(keycode, scene);
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
