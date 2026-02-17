/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/16 23:47:11 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Select the object by left clicked.
 *
 * @param button
 * @param x
 * @param y
 * @param scene
 * @return int
 */
int	mouse_hook(int button, int x, int y, t_scene *scene)
{
	double	t;
	t_ray	ray;

	if (button != 1)
		return (0);
	ray = get_ray(x, y, scene->cam);
	scene->selected_obj = find_closest_obj(scene, ray, &t);
	if (scene->selected_obj)
	{
		scene->mode = OBJECT;
		ft_putstr_fd("Selected : ", 1);
		ft_putendl_fd(get_type(scene->selected_obj), 1);
	}
	else
	{
		scene->mode = CAMERA;
		ft_putendl_fd("Selected : CAMERA(Home)", 1);
	}
	scene->render_flag = 1;
	return (0);
}
