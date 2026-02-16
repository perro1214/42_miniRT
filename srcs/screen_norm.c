/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:29:25 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 00:30:44 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	clamp_tan_fov(double fov);

t_ray	get_ray(int px, int py, t_camera *cam)
{
	double	x_n;
	double	y_n;
	t_vec3	ray_dir;

	x_n = (2.0 * (px + 0.5) * cam->inv_width - 1.0) * cam->aspect_ratio
		* cam->render_scale;
	y_n = (1.0 - 2.0 * (py + 0.5) * cam->inv_height) * cam->render_scale;
	ray_dir = vec3_add(cam->curr.normal, vec3_add(vec3_scale(cam->right, x_n),
				vec3_scale(cam->up, y_n)));
	return (ray_init(cam->curr.pos, ray_dir));
}

void	init_camera(t_camera *cam, t_scene *scene)
{
	scene->cam->curr.pos = scene->cam->pos;
	scene->cam->curr.normal = vec3_normalize(scene->cam->dir);
	scene->cam->curr.angle = vec3_init(0, 0, 0);
	cam->aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
	cam->render_scale = tan((clamp_tan_fov(cam->fov) * M_PI / 180.0) * 0.5);
	cam->inv_width = 1.0 / (double)WIN_WIDTH;
	cam->inv_height = 1.0 / (double)WIN_HEIGHT;
}

static double	clamp_tan_fov(double fov)
{
	if (fov == 0)
		return (EPSILON);
	else if (fov == 180)
		return (180 - EPSILON);
	else
		return (fov);
}
