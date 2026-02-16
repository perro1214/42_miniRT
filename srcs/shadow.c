#include "miniRT.h"

int	is_in_shadow(t_object *objects, t_light *light, t_vec3 hit_point,
		t_vec3 normal)
{
	t_ray		shadow_ray;
	t_vec3		light_dir;
	double		light_distance;
	double		t;
	t_object	*obj;

	light_dir = vec3_sub(light->curr.pos, hit_point);
	light_distance = vec3_norm(light_dir);
	light_dir = vec3_normalize(light_dir);
	shadow_ray.origin = vec3_add(hit_point, vec3_scale(normal, EPSILON));
	shadow_ray.direction = light_dir;
	obj = objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			t = hit_sphere(obj, shadow_ray);
		else if (obj->type == PLANE)
			t = hit_plane(obj, shadow_ray);
		else if (obj->type == CYLINDER)
			t = hit_cylinder(obj, shadow_ray);
		else if (obj->type == CONE)
			t = hit_cone(obj, shadow_ray);
		else
			t = -1;
		if (t > EPSILON && t < light_distance)
			return (1);
		obj = obj->next;
	}
	return (0);
}
