/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_action_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:14 by hayato            #+#    #+#             */
/*   Updated: 2026/02/17 03:42:16 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	set_key_object(int keycode, t_camera *cam, t_vec3 *axis,
				double *angle);
static void	rotate_object_basis(t_object *obj, t_vec3 axis, double angle);
static int	set_key_camera(int keycode, t_camera *cam, t_vec3 *axis,
				double *angle);

void	rotate_object(int keycode, t_scene *scene)
{
	t_object	*obj;
	t_vec3		axis;
	double		angle;
	double		half_h;
	t_vec3		mid;

	obj = scene->selected_obj;
	if (!obj || !set_key_object(keycode, scene->cam, &axis, &angle))
		return ;
	if (obj->type == CYLINDER || obj->type == CONE)
	{
		half_h = 0;
		if (obj->type == CYLINDER)
			half_h = obj->data.cy.half_h;
		else if (obj->type == CONE)
			half_h = obj->data.co.half_h;
		mid = vec3_add(obj->curr.pos, vec3_scale(obj->curr.normal, half_h));
		rotate_object_basis(obj, axis, angle);
		obj->curr.pos = vec3_sub(mid, vec3_scale(obj->curr.normal, half_h));
	}
	else
		rotate_object_basis(obj, axis, angle);
}

static int	set_key_object(int keycode, t_camera *cam, t_vec3 *axis,
		double *angle)
{
	double	rot_step;

	rot_step = 0.1;
	if (keycode == XK_i || keycode == XK_k)
	{
		*axis = cam->right;
		if (keycode == XK_i)
			*angle = rot_step;
		else
			*angle = -rot_step;
	}
	else if (keycode == XK_l || keycode == XK_j)
	{
		*axis = cam->curr.normal;
		if (keycode == XK_l)
			*angle = -rot_step;
		else
			*angle = rot_step;
	}
	else
		return (0);
	return (1);
}

static void	rotate_object_basis(t_object *obj, t_vec3 axis, double angle)
{
	obj->curr.normal = vec3_rotate_axis(obj->curr.normal, axis, angle);
	obj->curr.normal = vec3_normalize(obj->curr.normal);
	obj->right = vec3_rotate_axis(obj->right, axis, angle);
	obj->right = vec3_normalize(obj->right);
	obj->up = vec3_rotate_axis(obj->up, axis, angle);
	obj->up = vec3_normalize(obj->up);
}

void	rotate_camera(int keycode, t_scene *scene)
{
	t_camera	*cam;
	t_vec3		axis;
	double		angle;

	cam = scene->cam;
	if (!cam || !set_key_camera(keycode, cam, &axis, &angle))
		return ;
	cam->curr.normal = vec3_rotate_axis(cam->curr.normal, axis, angle);
	cam->right = vec3_rotate_axis(cam->right, axis, angle);
	cam->up = vec3_rotate_axis(cam->up, axis, angle);
	cam->curr.normal = vec3_normalize(cam->curr.normal);
	cam->right = vec3_normalize(vec3_cross(cam->up, cam->curr.normal));
	cam->up = vec3_normalize(vec3_cross(cam->curr.normal, cam->right));
}

static int	set_key_camera(int keycode, t_camera *cam, t_vec3 *axis,
		double *angle)
{
	double	rot_step;

	rot_step = 0.1;
	if (keycode == XK_i || keycode == XK_k)
	{
		*axis = cam->right;
		if (keycode == XK_i)
			*angle = -rot_step;
		else
			*angle = rot_step;
	}
	else if (keycode == XK_l || keycode == XK_j)
	{
		*axis = vec3_init(0, 1, 0);
		if (keycode == XK_j)
			*angle = -rot_step;
		else
			*angle = rot_step;
	}
	else
		return (0);
	return (1);
}
