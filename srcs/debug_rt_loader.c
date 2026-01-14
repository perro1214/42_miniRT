/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_rt_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:25:42 by htsutsum          #+#    #+#             */
/*   Updated: 2026/01/14 18:14:20 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void debug_print_objects(t_object *obj);


int	main(int argc, char **argv)
{
	t_object	*objs;

	objs = NULL;
	if (parse_arguments(argc, argv))
		return (1);
	printf("Source file: %s\n", argv[1]);
    if (rt_loader(&objs, argv[1]) != 0)
    {
        printf("Error: Failed to load scene from %s\n", argv[1]);
        free_objects(objs);
        return (1);
    }

    // デバッグ表示
    printf("Source file: %s\n", argv[1]);
	debug_print_objects(objs);

	return (0);
}

static void debug_print_objects(t_object *obj)
{
    int i = 0;
    while (obj != NULL)
    {
        printf("--- Object [%d] ---\n", i++);
        printf("Type: %d (0:SPHERE, 1:PLANE, 2:CYLINDER)\n", obj->type);
        printf("Point: (%f, %f, %f)\n", obj->point.x, obj->point.y, obj->point.z);
        printf("Color: (%f, %f, %f)\n", obj->color.x, obj->color.y, obj->color.z);

        if (obj->type == SPHERE)
            printf("Sphere Radius: %f\n", obj->data.sp.radius);
        else if (obj->type == PLANE)
            printf("Plane Normal: (%f, %f, %f)\n", obj->data.pl.normal.x, obj->data.pl.normal.y, obj->data.pl.normal.z);
        else if (obj->type == CYLINDER)
        {
            printf("Cylinder Normal: (%f, %f, %f)\n", obj->data.cy.normal.x, obj->data.cy.normal.y, obj->data.cy.normal.z);
            printf("Cylinder Radius: %f, Height: %f\n", obj->data.cy.radius, obj->data.cy.height);
        }
        obj = obj->next;
        printf("\n");
    }
}
