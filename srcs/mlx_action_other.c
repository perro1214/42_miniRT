/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_other.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/12 13:02:37 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief the callback function for the expose window event.
 *
 * @param scene
 * @return int
 */
int	expose_hook(t_scene *scene)
{
	render_scene(scene);
	return (0);
}

/**
 * @brief the callback function for the window close event.
 *
 * @param scene
 * @return int
 */
int	close_window(t_scene *scene)
{
	mlx_destroy_image(scene->mlx->mlx, scene->mlx->img);
	mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
	free(scene->mlx->mlx);
	free_scene(scene);
	exit(0);
	return (0);
}
