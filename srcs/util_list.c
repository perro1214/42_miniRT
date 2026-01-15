/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:36:17 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/15 02:08:08 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void free_objects(t_object *objs)
{
	t_object *tmp;

	while (objs != NULL)
	{
		tmp = objs->next;
		free(objs);
		objs = tmp;
	}
}

void free_lights(t_light *lts)
{
	t_light *tmp;

	while ( lts != NULL)
	{
		tmp = lts->next;
		free(lts);
		lts = tmp
	}
}

void	add_object_to_list(t_object **head, t_object *new_obj)
{
	if (new_obj == NULL)
		return ;
	new_obj->next = *head;
	*head = new_obj;
}

void	add_light_to_list(t_light **head, t_light *new_lt)
{
	if (new_lt == NULL)
		return ;
	new_lt->next = *head;
	*head = new_lt;
}
