/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:36:17 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/21 23:43:59 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	add_new_object(t_scene *scene, char **rt_data)
{
    t_object *new;

    new = ft_calloc(1, sizeof(t_object));
    if (!new) return (1);

    int status = 1;
    if (ft_strcmp(rt_data[0], "sp") == 0)
		status = set_sphere(new, rt_data);
    else if (ft_strcmp(rt_data[0], "pl") == 0)
		status = set_plane(new, rt_data);
    else if (ft_strcmp(rt_data[0], "cy") == 0)
		status = set_cylinder(new, rt_data);
    if (status != 0)
        return (free(new), 1);
    add_object_to_list(&(scene->objs), new);
    return (0);
}

void	add_object_to_list(t_object **head, t_object *new_obj)
{
	if (new_obj == NULL)
		return ;
	new_obj->next = *head;
	*head = new_obj;
}

void	free_objects(t_object *objs)
{
	t_object *tmp;

	while (objs != NULL)
	{
		tmp = objs->next;
		free(objs);
		objs = tmp;
	}
}
