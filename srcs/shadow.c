#include "miniRT.h"

/*
** 影の判定
**
** 戻り値:
**   1: 影の中
**   0: 影の中ではない
*/

int	is_in_shadow(t_object *objects, t_light *light, t_vec3 hit_point,
		t_vec3 normal)
{
	t_ray		shadow_ray;
	t_vec3		light_dir;
	double		light_distance;
	double		t;
	t_object	*obj;

	// 光源への方向と距離を計算
	light_dir = vec3_sub(light->curr.pos, hit_point);
	light_distance = vec3_norm(light_dir);
	light_dir = vec3_normalize(light_dir);
	// シャドウレイの始点を少しずらす（自己交差防止）
	shadow_ray.origin = vec3_add(hit_point, vec3_scale(normal, EPSILON));
	shadow_ray.direction = light_dir;
	// 全てのオブジェクトと交差判定
	obj = objects;
	while (obj)
	{
		if (obj->type == SPHERE)
			t = hit_sphere(obj, shadow_ray);
		else if (obj->type == PLANE)
			t = hit_plane(obj, shadow_ray);
		else
			t = -1;
		// 光源より近い位置に物体があれば影
		if (t > EPSILON && t < light_distance)
			return (1);
		obj = obj->next;
	}
	return (0);
}
