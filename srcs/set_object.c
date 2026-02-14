/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:24:08 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/15 06:20:00 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	init_object_transforms(t_object *obj);

/**
 * ex.
 * sp 0.0,0.0,20.6 12.6 10,0,255
 * type : sp
 * position : 0.0,0.0.20.6
 * diameter : 12.6
 * color [0, 255]: 10,0,255
 * rt_data size : 4
 *
 * @brief loads sphere data.
 *
 */
int	set_sphere(t_object *obj, char **rt_data)
{
	int	status;

	status = 0;
	if (ft_count_tab(rt_data) != 4)
		return (log_error("Sphere: Invalid number of arguments"), 1);
	obj->type = SPHERE;
	obj->pos = str_to_vec3(rt_data[1], &status);
	obj->data.sp.radius = get_double(rt_data[2], &status) / 2.0;
	obj->color = str_to_vec3(rt_data[3], &status);
	if (status || !is_valid_color(obj->color) || obj->data.sp.radius <= 0)
		return (log_error("Sphere: Invalid data values"), 1);
	obj->color = color_to_unit(obj->color);
	init_object_transforms(obj);
	return (0);
}

/**
 * ex.
 * pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225 1
 * type : pl
 * position : 0.0,0.0,-10.0
 * direction [-1, 1]: 0.0,1.0,0.0
 * color [0, 255]: 0,0,255
 * checker_flag [0 or 1] : 1
 * rt_data size : 5
 *
 * @brief loads plane data.
 *
 */
int	set_plane(t_object *obj, char **rt_data)
{
	int	status;

	status = 0;
	if (ft_count_tab(rt_data) != 5)
		return (log_error("Plane: Invalid number of arguments"), 1);
	obj->type = PLANE;
	obj->pos = str_to_vec3(rt_data[1], &status);
	obj->data.pl.normal = str_to_vec3(rt_data[2], &status);
	obj->color = str_to_vec3(rt_data[3], &status);

	if (status || !is_valid_color(obj->color)
		|| !is_valid_normal(obj->data.pl.normal)
		|| !is_valid_checker_flag(rt_data[4]))
		return (log_error("Plane: Invalid data or normal"), 1);
	obj->color = color_to_unit(obj->color);
	obj->data.pl.normal = vec3_normalize(obj->data.pl.normal);
	obj->data.pl.checker_flag = ft_atoi(rt_data[4]);
	init_object_transforms(obj);
	return (0);
}

/**
 * ex.
 * cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
 * type : cy
 * position : 50.0,0.0.20.6
 * direction : [ -1, 1] :0.0,0.0,1.0
 * diameter : 14.2
 * height : 21.42
 * color [0, 255] : 10,0,255
 * rt_data size : 6
 *
 * @brief loads cylinder data.
 *
 */
int	set_cylinder(t_object *obj, char **rt_data)
{
	int	status;

	status = 0;
	if (ft_count_tab(rt_data) != 6)
		return (log_error("Cylinder: Invalid number of arguments"), 1);
	obj->type = CYLINDER;
	obj->pos = str_to_vec3(rt_data[1], &status);
	obj->data.cy.normal = str_to_vec3(rt_data[2], &status);
	obj->data.cy.radius = get_double(rt_data[3], &status) / 2.0;
	obj->data.cy.height = get_double(rt_data[4], &status);
	obj->color = str_to_vec3(rt_data[5], &status);
	if (status || !is_valid_color(obj->color)
		|| !is_valid_normal(obj->data.cy.normal) || obj->data.cy.radius <= 0
		|| obj->data.cy.height <= 0)
		return (log_error("Cylinder: Invalid data or normal data"), 1);
	obj->color = color_to_unit(obj->color);
	obj->data.cy.normal = vec3_normalize(obj->data.cy.normal);
	init_object_transforms(obj);
	return (0);
}

/**
 * @brief Initializes the transform state of the object.
 */
static void	init_object_transforms(t_object *obj)
{
	t_vec3 world_up;

	obj->curr.pos = obj->pos;
	obj->curr.angle = vec3_init(0, 0, 0);
	if (obj->type == PLANE)
		obj->curr.normal = obj->data.pl.normal;
	else if (obj->type == CYLINDER)
		obj->curr.normal = obj->data.cy.normal;
	else if (obj->type == SPHERE)
		obj->curr.normal = vec3_init(0, 1, 0);
	world_up = vec3_init(0, 1, 0);
	if (fabs(obj->curr.normal.y) > 0.9999)
		world_up = vec3_init(0, 0, 1);
	obj->right = vec3_normalize(vec3_cross(world_up, obj->curr.normal));
    obj->up = vec3_normalize(vec3_cross(obj->curr.normal, obj->right));
}
