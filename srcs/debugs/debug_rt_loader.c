/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_rt_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htsutsum <htsutsum@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:25:42 by htsutsum          #+#    #+#             */
/*   Updated: 2026/02/10 04:18:48 by htsutsum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void print_vec3(char *name, t_vec3 v)
{
    printf("%s: (%.2f, %.2f, %.2f) ", name, v.x, v.y, v.z);
}

static void print_color(t_vec3 c)
{
    printf("Color: [%.0f, %.0f, %.0f]\n", c.x, c.y, c.z);
}

static void print_scene(t_scene *scene)
{
    printf("\n--- SCENE DATA DUMP ---\n");
    if (scene->amb)
    {
        printf("[Ambient]  Ratio : %.2f | ", scene->amb->ratio);
        print_color(scene->amb->color);
    }
    if (scene->cam)
    {
        printf("[Camera]   ");
        print_vec3("Pos", scene->cam->pos);
        print_vec3("Dir", scene->cam->dir);
        printf("FOV: %.1f\n", scene->cam->fov);
    }
    t_light *l = scene->ligs;
    while (l)
    {
        printf("[Light]    ");
        print_vec3("Pos", l->pos);
        printf("Ratio: %.2f | ", l->intensity);
        print_color(l->color);
        l = l->next;
    }
    t_object *o = scene->objs;
    while (o)
    {
        printf("[Object]   Type: %-8s | ", (o->type == SPHERE ? "SPHERE" : (o->type == PLANE ? "PLANE" : "CYLINDER")));
        print_vec3("Pos", o->pos);
        if (o->type == SPHERE)
            printf("Radius: %.2f | ", o->data.sp.radius);
        else if (o->type == PLANE)
            print_vec3("Normal", o->data.pl.normal);
        else if (o->type == CYLINDER)
        {
            print_vec3("Normal", o->data.cy.normal);
            printf("Rad: %.2f Height: %.2f | ", o->data.cy.radius, o->data.cy.height);
        }
        print_color(o->color);
        o = o->next;
    }
    printf("=====================================\n\n");
}

int main(int argc, char **argv)
{
    t_scene scene;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./debug_rt_loader <rtfile.rt>\n");
        return (1);
    }

    scene.cam = NULL;
    scene.amb = NULL;
    scene.ligs = NULL;
    scene.objs = NULL;

    printf("--- Loading file: %s ---\n", argv[1]);
    if (rt_loader(&scene, argv[1]) != 0)
    {
        fprintf(stderr, "Error: Failed to load scene.\n");
        free_scene(&scene);
        return (1);
    }

    print_scene(&scene);

    printf("--- Validating scene integrity ---\n");
    if (is_valid_scene(&scene) != 0)
    {
        free_scene(&scene);
        return (1);
    }

    printf("Result: All data loaded and validated successfully.\n");
    free_scene(&scene);
    return (0);
}
