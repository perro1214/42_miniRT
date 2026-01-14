/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:36:17 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/14 17:42:29 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void free_objects(t_object *objs)
{
	t_object *tmp;

	while(objs != NULL)
	{
		tmp = objs->next;
		free(objs);
		objs = tmp;
	}
}

void	add_object_to_list(t_object **head, t_object *new_obj)
{
	if (!new_obj)
		return ;
	new_obj->next = *head;
	*head = new_obj;
}
