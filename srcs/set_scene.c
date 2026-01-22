/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:42:56 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/22 01:27:31 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	add_light_to_list(t_light **head, t_light *new_light);

/* A 0.2 255,255,255
 * type : A
 * ratio [0.0  1.0] : 0.2
 * color [0 - 255] : 255,255,25
 * size 3
 * @brief load an ambient light data.
 */
int	set_ambient(t_scene *scene, char **rt_data)
{
	int	status;

	status = 0;
	if (ft_count_tab(rt_data) != 3)
		return (log_error("Ambient : Invalid number of arguments"), 1);
	if (scene->amb)
		return (log_error("Ambient: Symbol 'A' declared more than once"), 1);
	scene->amb = ft_calloc(1, sizeof(t_ambient));
	if (!scene->amb)
		return (1);
	scene->amb->ratio = get_double(rt_data[1], &status);
	scene->amb->color = str_to_vec3(rt_data[2], &status);
	if (status || !is_in_range(scene->amb->ratio, 0.0, 1.0)
		|| !is_valid_color(scene->amb->color))
	{
		log_error("Ambient: Invalid ratio or color range");
		return (free(scene->amb), scene->amb = NULL, 1);
	}
	return (0);
}

/* C -50.0,0 0,0,1 70
 * type : C
 * position : -50,0,0
 * direction [-1, 1] : 0.0,0.0.1.0
 * fov [0 - 70] : 70
 * @brief load a camera data.
 *
 */
int	set_camera(t_scene *scene, char **rt_data)
{
	int	status;

	status = 0;
	if (ft_count_tab(rt_data) != 4)
		return (log_error("Camera: Invalid number of arguments"), 1);
	if (scene->cam)
		return (log_error("Camera: Symbol 'C' declared more than once"), 1);
	scene->cam = ft_calloc(1, sizeof(t_camera));
	if (!scene->cam)
		return (1);
	scene->cam->position = str_to_vec3(rt_data[1], &status);
	scene->cam->direction = str_to_vec3(rt_data[2], &status);
	scene->cam->fov = atof(rt_data[3]);
	if (status)
		log_error("Camera: Vector parsing failed");
	else if (!is_normalized(scene->cam->direction))
		log_error("Camera: Direction vector is not normalized");
	else if (!is_in_range(scene->cam->fov, 0.1, 179.9))
		log_error("Camera: FOV out of range [0.1, 179.9]");
	else
		return (0);
	return (free(scene->cam), scene->cam = NULL, 1);
	return (0);
}

/* L -40.0,50.0,0.0 0.6 10,0,255
 * type : L
 * position : -40.0, 50.0, 0.0
 * intensity [0.0, 1.0] : 0.6
 * color [0, 255] : 10,0,255
 * @brief load a light data.
 */
int	set_light(t_scene *scene, char **rt_data)
{
	t_light	*new;
	int		status;

	if (ft_count_tab(rt_data) != 4)
		return (log_error("Light : Invalid number of arguments"), 1);
	new = ft_calloc(1, sizeof(t_light));
	if (!new)
		return (1);
	new->position = str_to_vec3(rt_data[1], &status);
	new->intensity = atof(rt_data[2]);
	new->color = str_to_vec3(rt_data[3], &status);
	if (status || !is_in_range(new->intensity, 0.0, 1.0)
		|| !is_valid_color(new->color))
	{
		free(new);
		return (log_error("Light: Invalid data values"), 1);
	}
	add_light_to_list(&(scene->ligs), new);
	return (0);
}

void	free_lights(t_light *lights)
{
	t_light	*tmp;

	while (lights)
	{
		tmp = lights->next;
		free(lights);
		lights = tmp;
	}
}

static void	add_light_to_list(t_light **head, t_light *new_light)
{
	if (!new_light)
		return ;
	new_light->next = *head;
	*head = new_light;
}
